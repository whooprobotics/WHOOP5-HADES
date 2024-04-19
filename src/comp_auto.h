#ifndef COMP_AUTO
#define COMP_AUTO

#include "rev/rev.hh"
#include "api.h"

void comp_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless, std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem& intake);

#endif