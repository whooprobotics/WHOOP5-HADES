#include <vector>
#include "main.h"
#include "rev/rev.hh"


// motor ports
pros::MotorGroup left_mg({ 7, 5, 4, 3 });
pros::MotorGroup right_mg({8, 6, 19, 20});
pros::MotorGroup intake({ 14, -4 });

// sensor inputs
const int IMU_PORT = 9;
const int H_ROTATION_PORT = 10;
const int V_ROTATION_PORT = 18;
pros::IMU imu = pros::IMU(IMU_PORT);
pros::Rotation fwd = pros::Rotation(V_ROTATION_PORT, true);
pros::Rotation lat = pros::Rotation(H_ROTATION_PORT);