#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "main.h"
#include "rev/rev.hh"
#include "path/Wing.h"
#include "path/Intake.h"

const int WING_OUT = 1;
const int WING_IN = 0;

const int ODOM_UP = 1;
const int ODOM_DOWN = 0;

extern std::shared_ptr<rev::AsyncRunner> odom_runner;
extern std::shared_ptr<rev::AsyncRunner> reckless_runner;
extern std::shared_ptr<rev::AsyncRunner> turn_runner;


extern std::shared_ptr<rev::TwoRotationInertialOdometry> odom;
extern std::shared_ptr<rev::SkidSteerChassis> chassis;

extern std::shared_ptr<rev::Reckless> reckless;
extern std::shared_ptr<rev::CampbellTurn> turn;


// motor ports
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern pros::MotorGroup intake;

// sensor inputs
extern pros::IMU imu;
extern pros::Rotation fwd;
extern pros::Rotation lat;

// Beam Break
extern pros::ADIDigitalIn beam_break;
extern IntakeSystem intake_system;

// hydraulics

extern pros::ADIDigitalOut backWingL;
extern pros::ADIDigitalOut backWingR;
extern pros::ADIDigitalOut frontWings;
extern pros::ADIDigitalOut odomHydraulic;

extern Wings wings;

#endif