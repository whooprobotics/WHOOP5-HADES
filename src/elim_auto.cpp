#include "rev/rev.hh"
#include "path/Path.h"
#include "api.h"

void elim_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
                 std::shared_ptr<rev::CampbellTurn> turn, const Wings& wings, const IntakeSystem& intake) {
    Path path;
    // intake balls
    path.add_straight(Straight({  3_in, 0_in, 0_deg}, 0_in, MOTOR_SPEED::MID));
    path.add_turn(MyTurn(-60_deg));
    path.add_straight(Straight({ 13_in, -20_in, 0_deg }, 0_in, MOTOR_SPEED::MID));
    path.add_turn(MyTurn(-45_deg));
    path.add_wing_control(Wing(OPEN, BACK_LEFT));


    for (int i = 0; i < 5; i++) {
        path.add_straight(Straight({ 8_in, -15_in, 0_deg }, 0_in, MOTOR_SPEED::MID));
        path.add_straight(Straight({ 13_in, -20_in, 0_deg }, 0_in, MOTOR_SPEED::MID));
    }

    path.add_straight(Straight({ 8_in,  -15_in, 0_deg}, 0_in, MOTOR_SPEED::MID));

    path.add_wing_control(Wing(CLOSE, BACK_LEFT));

    path.add_straight(Straight({   3_in,  73_in, 0_deg}, 0_in, MOTOR_SPEED::MID));
    path.add_straight(Straight({  32_in,  93_in, 0_deg}, 0_in, MOTOR_SPEED::MID));


    //path.add_turn(MyTurn(131_deg - 180_deg));
    //path.add_straight(Straight({   5_in,  13_in, 0_deg}, 0_in, MOTOR_SPEED::MID));
    /*
    // drive to other side
    path.add_straight(Straight({   5_in,  72_in, 0_deg}, 5_in, MOTOR_SPEED::MID));
    path.add_straight(Straight({  12_in,  86_in, 0_deg}, 3_in, MOTOR_SPEED::SLOW));

    path.add_straight(Straight({  30_in,  97_in, 0_deg}, 3_in, MOTOR_SPEED::SLOW));
    path.add_straight(Straight({  35_in,  98_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW));
*/
    path.go(reckless, turn, wings, intake);
}