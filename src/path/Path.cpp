#ifndef PATH_CPP
#define PATH_CPP
#include "Path.h"
#include "api.h"

const int TURN = 0;
const int STRAIGHT = 1;
const int WING_CONTROL = 2;
const int DELAY = 3;
const int INTAKE_RUN = 4;

void Path::add_straight(const Straight& straight) {
    double speed = 0.5;
    double glideSpeed = 0.3;
    QTime hardStop = 0.03_s;
    QTime softStop = 0.15_s;
    
    switch (straight.get_motor_speed())
    {
    case MOTOR_SPEED::SLOW:
        speed = 0.4;
        glideSpeed = 0.25;
        break;
    case MOTOR_SPEED::MID:
        //speed = 0.6;
        //speed = 0.6;
        //softStop = 0.28_s;
        //break;
    case MOTOR_SPEED::FAST:
        speed = 1.0;
        hardStop = 0.04_s;
        break;
    }

    if (straight.is_smooth_finish()) {
        hardStop = 0_s;
        softStop = 0_s;
    }

    if (next_is_turn.empty() || next_is_turn.back() != STRAIGHT) {
        next_is_turn.push(STRAIGHT);
        straight_segments.push(RecklessPath()
        .with_segment(RecklessPathSegment(
        std::make_shared<ConstantMotion>(speed),
        std::make_shared<PilonsCorrection>(4, 0.3_in),
        std::make_shared<SimpleStop>(hardStop, softStop, glideSpeed, straight.get_time_out()), straight.get_target(), straight.get_drop_early())));
    } else {
        straight_segments.back().with_segment(RecklessPathSegment(
        std::make_shared<ConstantMotion>(speed),
        std::make_shared<PilonsCorrection>(4, 0.3_in),
        std::make_shared<SimpleStop>(hardStop, softStop, glideSpeed, straight.get_time_out()), straight.get_target(), straight.get_drop_early()));
    }

    straights.push(straight);
}

void Path::add_delay(const Delay& delay) {
    delays.push(delay);
    next_is_turn.push(DELAY);
}

void Path::add_intake_control(const IntakeControl& control) {
    intake_controls.push(control);
    next_is_turn.push(INTAKE_RUN);
}

void Path::add_wing_control(const Wing& wing) {
    wing_controls.push(wing);
    next_is_turn.push(WING_CONTROL);
}

void Path::add_turn(const MyTurn& turn) {
    turns.push(turn);
    next_is_turn.push(TURN);
}

void Path::go(std::shared_ptr<Reckless> reckless, 
                std::shared_ptr<CampbellTurn> turnController, const Wings& wings, const IntakeSystem& intake) {
    if (straight_segments.empty() && turns.empty()
             && wing_controls.empty() && delays.empty() && intake_controls.empty()) return;

    int is_turn = next_is_turn.front();
    next_is_turn.pop();


    int i = 0;
    while (!straight_segments.empty() || !turns.empty() 
                || !wing_controls.empty() || !delays.empty() || !intake_controls.empty()) {
        if (is_turn == TURN) {
             MyTurn turn = turns.front();
             turns.pop();

            turnController->turn_to_target_absolute(turn.get_speed(), turn.get_angle());

            QTime time_out = turn.get_time_out();

            while (!turnController->is_completed() && time_out >= 0_s) {
                pros::delay(10);
                time_out -= 10_ms;
            }

            turnController->breakout();
        } else if (is_turn == STRAIGHT) {
            RecklessPath next_straight = straight_segments.front();
            straight_segments.pop();

            Straight straight = straights.front();
            straights.pop();

            reckless->go(next_straight);

            reckless->await();

        } else if (is_turn == DELAY) {
            Delay next = delays.front();
            delays.pop();

            pros::delay(next.get_delay());
        } else if (is_turn == INTAKE_RUN) {
            IntakeControl control = intake_controls.front();
            intake_controls.pop();

            switch (control.get_mode()) {
                case IN:
                    intake.intake.move_voltage(12000);
                    break;
                case OUT:
                    intake.intake.move_voltage(-12000);
                    break;
                case OUT_SLOW:
                    intake.intake.move_voltage(-10000);
                    break;
                case REST:
                    intake.intake.move_voltage(0);
                    break;
                case OUT_WITH_SENSE:
                    intake.intake.move_voltage(-12000);

                    for (int i = 0; i < 100; i++) {
                        if (intake.beam_break.get_value() == 0)
                            break;
                        pros::delay(10);
                    }

                    intake.intake.move_voltage(0);
                    break;
                case IN_WITH_SENSE:
                    intake.intake.move_voltage(12000);

                    for (int i = 0; i < 100; i++) {
                        if (intake.beam_break.get_value()) {
                            break;
                        }

                        pros::delay(10);
                    }

                    intake.intake.move_voltage(0);
            }
        } else {
            Wing next_wing = wing_controls.front();
            wing_controls.pop();

            switch (next_wing.get_type()) {
                case BACK_LEFT:
                    wings.backLeft.set_value(next_wing.get_direction());
                    break;
                case BACK_RIGHT:
                    wings.backRight.set_value(next_wing.get_direction());
                    break;
                case FRONT:
                    wings.front.set_value(next_wing.get_direction());
                    break;
            }
        }
        if (next_is_turn.size() != 0) {
            is_turn = next_is_turn.front();
            next_is_turn.pop();
        } else break;
    }
}

#endif