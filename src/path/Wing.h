#ifndef WING_H
#define WING_H

#include "api.h"

using port = pros::ADIDigitalOut;

enum WING_TYPE {
    BACK_LEFT, BACK_RIGHT, FRONT
};

enum WING_DIRECTION {
    CLOSE, OPEN
};

struct Wings {
public:
    const port& backLeft;
    const port& backRight;
    const port& front;
};

class Wing {
private:
    WING_DIRECTION direction;
    WING_TYPE type;
public:
    Wing(WING_DIRECTION direction, WING_TYPE type) : direction(direction), type(type) {  }

    WING_DIRECTION get_direction() { return direction; }
    WING_TYPE get_type() { return type; }
};

#endif