#ifndef TURN_H
#define TURN_H

#include "rev/rev.hh"

class MyTurn {
private:
    QAngle angle;
    double speed;
    bool go_through;
    QTime time_out;
public:
    MyTurn(QAngle angle, QTime time_out=9999999_s, double speed=0.7, bool go_through=false) : angle(angle), speed(speed), time_out(time_out), go_through(go_through) {  }
    MyTurn(const MyTurn& other) : angle(other.angle), speed(other.speed), go_through(go_through), time_out(other.time_out) {  }

    QAngle& get_angle() { return angle; }
    double get_speed() { return speed; }
    bool should_go_through() { return go_through; }
    QTime& get_time_out() { return time_out; }
};

#endif