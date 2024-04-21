#include "main.h"
#include "rev/rev.hh"
#include "globals.h"
#include "path/Path.h"

#include "comp_auto.h"
#include "elim_auto.h"
#include "skills_auto.h"
#include "comp_auto_passive.h"
#include "tuning.h"

using namespace rev;

void print_position(std::shared_ptr<TwoRotationInertialOdometry> odom) {
	pros::lcd::set_text(0, "X: " + std::to_string(odom->get_state().pos.x.convert(inch)));
	pros::lcd::set_text(1, "Y: " + std::to_string(odom->get_state().pos.y.convert(inch)));
	pros::lcd::set_text(2, "Heading: " + std::to_string(odom->get_state().pos.theta.convert(degree)));
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  chassis = std::make_shared<rev::SkidSteerChassis>(left_mg, right_mg);
	odom = std::make_shared<rev::TwoRotationInertialOdometry>(
    fwd,      // The forward sensor
    lat,      // The rightward sensor 
    imu,      // Inertial sensor
    63.89_mm,  // Diameter of forward wheel
    63.89_mm,  // Diameter of sideways wheel
    -1.125_in,  // How far to the right of the center of the robot the forward wheel is
    -1_in    // How far to the rear of the robot the lateral wheel is from the center
  );
  turn = std::make_shared<CampbellTurn>(chassis, odom, 0.18, 0.07);  
  reckless = std::make_shared<Reckless>(chassis, odom);

  odom_runner = std::make_shared<rev::AsyncRunner>(odom);
	reckless_runner = std::make_shared<rev::AsyncRunner>(reckless);
	turn_runner = std::make_shared<rev::AsyncRunner> (turn);

	pros::lcd::initialize();

  pros::delay(2000);
  odom->reset_position();

  
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
void autonomous() {
  odomHydraulic.set_value(ODOM_DOWN);
  //backWingL.set_value(WING_OUT);

  //comp_auto(odom, reckless, turn);
  //skills_auto(odom, reckless, turn);
  tuning(odom, reckless, turn, intake_system);
}

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


  //Path path;
  //path.add_straight(Straight({ 10_in, 0_in, 0_deg }, 0_in, MOTOR_SPEED::SLOW));
  //path.go(reckless, turn);
  autonomous();
  //print_position(odom);

	pros::Controller controller(pros::E_CONTROLLER_MASTER);
/*
R1 - back wings
L1 - front wings
L2 - intake
R2 - outake
*/

  odomHydraulic.set_value(ODOM_UP);

  bool rearWingsOut = false;
  bool frontWingsOut = false;
  bool odomUp = false;
  bool r1Down = false;
  bool l1Down = false;
  bool ADown = false;

	while (true) {
    print_position(odom);
    pros::lcd::set_text(3, "bb: " + std::to_string(beam_break.get_value()));
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

    if (controller.get_digital(DIGITAL_R1)) {
      if (!r1Down) {
        r1Down = true;
        rearWingsOut = !rearWingsOut;
        if (!rearWingsOut) {
          backWingL.set_value(WING_IN);
          backWingR.set_value(WING_IN);
        } else {
          backWingL.set_value(WING_OUT);
          backWingR.set_value(WING_OUT);
        }
      }
    } else {
      r1Down = false;
    }

     if (controller.get_digital(DIGITAL_L1)) {
      if (!l1Down) {
        l1Down = true;
        frontWingsOut = !frontWingsOut;
        if (!frontWingsOut) {
          frontWings.set_value(WING_IN);
        } else {
          frontWings.set_value(WING_OUT);
        }
      }
    } else {
      l1Down = false;
    }
  /*
     if (controller.get_digital(DIGITAL_A)) {
      if (!ADown) {
        ADown = true;
        odomUp = !odomUp;
        if (!odomUp) {
          odomHydraulic.set_value(ODOM_UP);
        } else {
          odomHydraulic.set_value(ODOM_DOWN);
        }
      }
    } else {
      ADown = false;
    }
    */

	left_mg.move_voltage((int)((double) (starting + turn)/150 * 12000));
	right_mg.move_voltage((int)((double) (starting - turn)/150 * 12000));


		if (controller.get_digital(DIGITAL_L2))
			intake.move_voltage(12000);
		else if (controller.get_digital(DIGITAL_R2))
			intake.move_voltage(-12000);
		else intake.move_voltage(0);

		pros::delay(20);
	}
}
