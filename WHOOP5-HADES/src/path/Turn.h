#ifndef TURN_H
#define TURN_H

class MyTurn {
private:
    QAngle angle;
public:
    MyTurn(QAngle angle) : angle(angle) {  }
    MyTurn(const MyTurn& other) : angle(other.angle) {  }

    QAngle get_angle() { return angle; }
};

#endif