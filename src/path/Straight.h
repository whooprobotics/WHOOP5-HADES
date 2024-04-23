#ifndef STRAIGHT_H
#define STRAITGHT_H
#include "rev/rev.hh"

using namespace rev;

enum MOTOR_SPEED {
    FAST, MID, SLOW, MID_STRAIGHT
};

class Straight {
private:
    const Position target;
    const QLength drop_early;
    const QTime time_out;
    const MOTOR_SPEED speed;
    const bool smooth_finish;
    
public:
    Straight(Position p, QLength drop_early, MOTOR_SPEED speed, bool smooth_finish=false, QTime time_out=99999_s) : target(p), drop_early(drop_early), speed(speed), time_out(time_out), smooth_finish(smooth_finish) {
    }

    const Position& get_target() const { return target; }
    const QLength& get_drop_early() const { return drop_early; }
    const MOTOR_SPEED& get_motor_speed() const { return speed; }
    const QTime get_time_out() const { return time_out; }
    const bool is_smooth_finish() const { return smooth_finish; }
};
#endif