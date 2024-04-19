#ifndef INTAKE_H
#define INTAKE_H

#include "api.h"

enum INTAKE_MODE {
    IN, OUT, REST, IN_WITH_SENSE
};

struct IntakeSystem {
    pros::ADIDigitalIn& beam_break;
    pros::MotorGroup& intake;
};

class IntakeControl {
private:
    INTAKE_MODE mode;
public:
    IntakeControl(INTAKE_MODE mode) { this->mode = mode; }
    INTAKE_MODE get_mode() { return mode; }
};

#endif