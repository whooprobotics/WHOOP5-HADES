#ifndef STRAIGHT_H
#define STRAITGHT_H
#include "rev/rev.hh"

using namespace rev;

enum MOTOR_SPEED {
    FAST, MID, SLOW
};

class Straight {
private:
    const Position target;
    const QTime time_out;
    const MOTOR_SPEED speed;
public:
    Straight(Position p, QTime time_out, MOTOR_SPEED speed) : target(p), time_out(time_out), speed(speed) {
    }

    const Position& get_target() const { return target; }
    const QTime& get_time_out() const { return time_out; }
    const MOTOR_SPEED& get_motor_speed() const { return speed; }
};
#endif