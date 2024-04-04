#include "main.h"
#include "rev/rev.hh"
#include "globals.h"
#include "path/Path.h"

using namespace rev;

void print_position(std::shared_ptr<TwoRotationInertialOdometry> odom) {
	pros::lcd::set_text(0, "X: " + std::to_string(odom->get_state().pos.x.convert(inch)));
	pros::lcd::set_text(1, "Y: " + std::to_string(odom->get_state().pos.y.convert(inch)));
	pros::lcd::set_text(2, "Heading: " + std::to_string(odom->get_state().pos.theta.convert(degree)));
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  	pros::lcd::initialize();

	odom = std::make_shared<rev::TwoRotationInertialOdometry>(
    fwd,      // The forward sensor
    lat,      // The rightward sensor 
    imu,      // Inertial sensor
    63.89_mm,  // Diameter of forward wheel
    63.89_mm,  // Diameter of sideways wheel
    -1.125_in,  // How far to the right of the center of the robot the forward wheel is
    -1_in    // How far to the rear of the robot the lateral wheel is from the center
  );
  chassis = std::make_shared<rev::SkidSteerChassis>(left_mg, right_mg);
  reckless = std::make_shared<Reckless>(chassis, odom);

  odom_runner = std::make_shared<rev::AsyncRunner>(rev::AsyncRunner(odom));
	reckless_runner = std::make_shared<rev::AsyncRunner>(reckless);

  turn = std::make_shared<CampbellTurn>(chassis, odom, 0.15, 0.05);  
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);


  pros::delay(2000);
  odom->reset_position();
  /*
for (int i = 0; i < 10000; i++) {
  print_position(odom);
  pros::delay(100);
}

Path path;

path.add_straight(Straight({  20_in,  0_in, 0_deg}, 0_s, MOTOR_SPEED::SLOW));
path.add_turn(MyTurn(-90_deg));
path.add_straight(Straight({ 20_in,   -10_in, 0_deg}, 0_s, MOTOR_SPEED::SLOW));

path.go(reckless, turn);
*/

	while (true) {
 // print_position(odom);

    int starting = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    if (abs(starting) < 25){
        starting = 0;
    }
    if (abs(turn) < 35){
        turn = 0;
    }

    if (abs(starting) < 25){
        starting = 0;
    }
    if (abs(turn) < 35){
        turn = 0;
    }

	left_mg.move_voltage((int)((double) (starting + turn)/150 * 12000));
	right_mg.move_voltage((int)((double) (starting - turn)/150 * 12000));

/*
		if (controller.get_digital(DIGITAL_L1))
			intake.move_voltage(12000);
		else if (controller.get_digital(DIGITAL_R1))
			intake.move_voltage(-12000);
		else intake.move_voltage(0);
*/
		pros::delay(20);
	}
}
