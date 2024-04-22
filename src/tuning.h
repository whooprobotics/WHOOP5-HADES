#include "rev/rev.hh"
#include "path/Path.h"
#include "globals.h"
#include "api.h"

void tuning(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
               std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem &intake)
{
    Path path;
    path.add_straight(Straight({20_in, 0_in, 0_deg},0_in, MOTOR_SPEED::FAST, false));



//path.add_straight(Straight({84.85_in, 63.64_in, 0_deg}, 2_in, MOTOR_SPEED::MID, true));
//path.add_straight(Straight({67.18_in, 45.96_in, 0_deg}, 4_in, MOTOR_SPEED::MID, true));

/*
path.add_intake_control(IN);
path.add_delay(200);
path.add_straight(Straight({63.64_in, 28.28_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false, 1000_ms));
path.add_intake_control(IN_WITH_SENSE);

path.add_turn(MyTurn(-45.0_deg));

path.add_straight(Straight({74.25_in, 24.75_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false));
path.add_wing_control(Wing(OPEN, FRONT));
path.add_delay(100);
path.add_straight(Straight({102.53_in, 45.96_in, 0_deg}, 0_in, MOTOR_SPEED::FAST, false, 800_ms));

path.add_intake_control(OUT);
path.add_straight(Straight({ 107_in,  44_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1.5_s));



path.add_intake_control(REST);
path.add_wing_control(Wing(CLOSE, FRONT));
*/
//path.add_straight(Straight({74.25_in, 31.82_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1500_ms));
//path.add_straight(Straight({49.50_in, 39.60_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 1500_ms));

//path.add_wing_control(Wing(OPEN, BACK_LEFT));



    path.go(reckless, turn, Wings{backWingL, backWingR, frontWings}, intake);
}