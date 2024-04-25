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
pros::MotorGroup left_mg({-17,-18,-19,-20 });//17,18,19,20
pros::MotorGroup right_mg({ 13,4, 10, 5});//-13, -4, -10, -5
pros::MotorGroup intake({ 16, -15 });
pros::MotorGroup climbing_mech({ 14, -2 });

// sensor inputs
const int IMU_PORT = 12;
const int H_ROTATION_PORT = 3;
const int V_ROTATION_PORT = 8;
pros::IMU imu = pros::IMU(IMU_PORT);
pros::Rotation fwd = pros::Rotation(V_ROTATION_PORT);
pros::Rotation lat = pros::Rotation(H_ROTATION_PORT);

// Beam Break
pros::ADIDigitalIn beam_break('D');
IntakeSystem intake_system { beam_break, intake };

pros::ADIDigitalOut backWingL = pros::ADIDigitalOut('C');
pros::ADIDigitalOut backWingR = pros::ADIDigitalOut('G');
pros::ADIDigitalOut frontWings = pros::ADIDigitalOut('H');
pros::ADIDigitalOut ratchet = pros::ADIDigitalOut('E');

Wings wings { backWingL, backWingR, frontWings };

pros::ADIDigitalOut odomHydraulic = pros::ADIDigitalOut('F');