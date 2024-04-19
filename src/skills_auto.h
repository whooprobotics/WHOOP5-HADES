#ifndef SKILLS_AUTO
#define SKILLS_AUTO

#include "rev/rev.hh"

void skills_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless, std::shared_ptr<rev::CampbellTurn> turn);

#endif