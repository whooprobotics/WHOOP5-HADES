#ifndef ELIM_AUTO
#define ELIM_AUTO

#include "rev/rev.hh"
#include "api.h"

void elim_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless, std::shared_ptr<rev::CampbellTurn> turn, const Wings& wings, const IntakeSystem& intake);

#endif