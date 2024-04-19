#include <vector>

#include "globals.h"
#include "rev/rev.hh"

std::shared_ptr<rev::AsyncRunner> odom_runner;
std::shared_ptr<rev::AsyncRunner> reckless_runner;
std::shared_ptr<rev::AsyncRunner> turn_runner;


std::shared_ptr<rev::TwoRotationInertialOdometry> odom;
std::shared_ptr<rev::SkidSteerChassis> chassis;

std::shared_ptr<rev::Reckless> reckless;
std::shared_ptr<rev::CampbellTurn> turn;


// motor ports
pros::MotorGroup left_mg({ -19, -7, -16, -11 });
pros::MotorGroup right_mg({15, 8, 12, 13});
pros::MotorGroup intake({ 14, -4 });

// sensor inputs
const int IMU_PORT = 1;
const int H_ROTATION_PORT = 10;
const int V_ROTATION_PORT = 5;
pros::IMU imu = pros::IMU(IMU_PORT);
pros::Rotation fwd = pros::Rotation(V_ROTATION_PORT, true);
pros::Rotation lat = pros::Rotation(H_ROTATION_PORT);

// Beam Break
pros::ADIDigitalIn beam_break('A');
IntakeSystem intake_system { beam_break, intake };

pros::ADIDigitalOut backWingL = pros::ADIDigitalOut('E');
pros::ADIDigitalOut backWingR = pros::ADIDigitalOut('G');
pros::ADIDigitalOut frontWings = pros::ADIDigitalOut('F');

Wings wings { backWingL, backWingR, frontWings };

pros::ADIDigitalOut odomHydraulic = pros::ADIDigitalOut('H');