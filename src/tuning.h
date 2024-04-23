#include "rev/rev.hh"
#include "path/Path.h"
#include "globals.h"
#include "api.h"

void tuning(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
               std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem &intake)
{
    Path path;
    path.add_wing_control(Wing(OPEN, BACK_LEFT));
    path.add_delay(1000);
    path.add_wing_control(Wing(OPEN,BACK_RIGHT));
    path.add_delay(1000);
    path.add_wing_control(Wing(OPEN, FRONT));

    path.go(reckless, turn, Wings{backWingL, backWingR, frontWings}, intake);
}