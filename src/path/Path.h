#ifndef PATH_H
#define PATH_H

#include <vector>
#include "rev/rev.hh"
#include "Straight.h"
#include "Turn.h"

using namespace rev;

class Path {
private:
    std::vector<RecklessPath> straight_segments;
    std::vector<MyTurn> turns;
    std::vector<bool> next_is_turn;
public:
    Path() {
    }

    void go(std::shared_ptr<Reckless>, std::shared_ptr<CampbellTurn>);

    void add_straight(const Straight&);

    void add_turn(MyTurn);
};

#endif