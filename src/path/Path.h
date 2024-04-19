#ifndef PATH_H
#define PATH_H

#include <queue>
#include "rev/rev.hh"
#include "Straight.h"
#include "Turn.h"
#include "Wing.h"
#include "Delay.h"
#include "api.h"
#include "Intake.h"

using namespace rev;

class Path {
private:
    std::queue<RecklessPath> straight_segments;
    std::queue<Straight> straights;
    std::queue<MyTurn> turns;
    std::queue<int> next_is_turn;
    std::queue<Wing> wing_controls;
    std::queue<Delay> delays;
    std::queue<IntakeControl> intake_controls;
public:
    Path() {
    }

    void go(std::shared_ptr<Reckless>, std::shared_ptr<CampbellTurn>, const Wings&, const IntakeSystem& intake);

    void add_straight(const Straight&);
    void add_turn(const MyTurn&);
    void add_wing_control(const Wing&);
    void add_delay(const Delay&);
    void add_intake_control(const IntakeControl& control);
};

#endif