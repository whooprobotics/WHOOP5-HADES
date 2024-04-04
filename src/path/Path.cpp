#include "Path.h"

void Path::add_straight(const Straight& straight) {
    double speed = 0;
    switch (straight.get_motor_speed())
    {
    case MOTOR_SPEED::SLOW:
        speed = 0.4;
        break;
    case MOTOR_SPEED::MID:
        speed = 0.7;
        break;
    case MOTOR_SPEED::FAST:
        speed = 1.0;
        break;
    }

    if (next_is_turn.empty() || next_is_turn.at(next_is_turn.size() - 1)) {
        next_is_turn.push_back(false);
        straight_segments.push_back(RecklessPath()
        .with_segment(RecklessPathSegment(
        std::make_shared<CascadingMotion>(speed, 1.1, 1.1,
                                          60_in / second, 0.07),
        std::make_shared<PilonsCorrection>(1.3, 0.5_in),
        std::make_shared<SimpleStop>(0.02_s, 0.15_s, 0.2), straight.get_target())));
    } else {
        next_is_turn.push_back(true);
        straight_segments.at(straight_segments.size() - 1).with_segment(RecklessPathSegment(
        std::make_shared<CascadingMotion>(speed, 1.1, 1.1,
                                          60_in / second, 0.07),
        std::make_shared<PilonsCorrection>(1.3, 0.5_in),
        std::make_shared<SimpleStop>(0.02_s, 0.15_s, 0.2), straight.get_target()));
    }
}

void Path::add_turn(MyTurn turn) {
    turns.push_back(turn);
}

void Path::go(std::shared_ptr<Reckless> reckless, std::shared_ptr<CampbellTurn> turnController) {
    if (straight_segments.empty() && turns.empty()) return;

    bool is_turn = next_is_turn.front();
    next_is_turn.erase(next_is_turn.begin());

    while (!straight_segments.empty() || !turns.empty()) {
        if (is_turn) {
            MyTurn& turn = turns.front();
            turns.erase(turns.begin());

            turnController->turn_to_target_absolute(0.7, turn.get_angle());
            turnController->await();
            pros::delay(5000);
        } else {
            RecklessPath next_straight = straight_segments.front();
            straight_segments.erase(straight_segments.begin());

            reckless->go(next_straight);
            reckless->await();
        }

        is_turn = next_is_turn.front();
        next_is_turn.erase(next_is_turn.begin());
    }
}