#include "rev/rev.hh"
#include "path/Path.h"
#include "globals.h"
#include "api.h"

void tuning(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
               std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem &intake)
{
    Path path;
    //path.add_straight(Straight({20_in, 0_in, 0_deg},0_in, MOTOR_SPEED::MID, false));
    path.add_turn(MyTurn(90.0_deg));

    path.go(reckless, turn, Wings{backWingL, backWingR, frontWings}, intake);
}