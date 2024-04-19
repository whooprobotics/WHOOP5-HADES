#include "main.h"
#include "rev/rev.hh"
#include "path/Path.h"

void skills_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless, std::shared_ptr<rev::CampbellTurn> turn) {
    odom->reset_position();
    Path path;


    //path.go(reckless, turn);
}