#include <vector>
#include "main.h"
#include "rev/rev.hh"
#include <memory>

std::shared_ptr<rev::AsyncRunner> odom_runner;
std::shared_ptr<rev::AsyncRunner> reckless_runner;


std::shared_ptr<rev::TwoRotationInertialOdometry> odom;
std::shared_ptr<rev::SkidSteerChassis> chassis;

std::shared_ptr<rev::Reckless> reckless;
std::shared_ptr<rev::CampbellTurn> turn;

// motor ports
pros::MotorGroup left_mg({ -6, -19, -20, -15 });
pros::MotorGroup right_mg({11, 4, 8, 5});
//pros::MotorGroup intake({ 10, -18 });

// sensor inputs
const int IMU_PORT = 7;
const int H_ROTATION_PORT = 10;
const int V_ROTATION_PORT = 18;
pros::IMU imu = pros::IMU(IMU_PORT);
pros::Rotation fwd = pros::Rotation(V_ROTATION_PORT, true);
pros::Rotation lat = pros::Rotation(H_ROTATION_PORT);