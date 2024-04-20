#include "rev/rev.hh"
#include "path/Path.h"
#include "globals.h"
#include "api.h"

void comp_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
               std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem &intake)
{
    Path path;

    // get the bottom left ball
    path.add_straight(Straight({28_in, 3_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 400_ms));
    path.add_intake_control(IN);
    path.add_straight(Straight({30_in, 2.5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 2000_ms));
    path.add_intake_control(IN_WITH_SENSE);

    // drop if off for Zeus to grab
    path.add_turn(MyTurn(135_deg, 700_ms));
    path.add_straight(Straight({36_in, 30_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1300_ms));
    path.add_intake_control(OUT_SLOW);
    path.add_delay(600);
    path.add_intake_control(REST);
    path.add_straight(Straight({  38_in,  18_in, 0_deg }, 0_in, MOTOR_SPEED::MID,false,500_ms));

    // Go back for the second ball on the left
    path.add_turn(MyTurn(-45_deg, 600_ms));
    path.add_straight(Straight({56_in, -10_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 500_ms));
    path.add_intake_control(IN);
    path.add_straight(Straight({54_in, -5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 9999_s));
    path.add_intake_control(IN_WITH_SENSE);


    /*
    path.add_turn(MyTurn(70_deg));
    path.add_intake_control(OUT_SLOW);
    path.add_delay(400);
    path.add_intake_control(REST);
    path.add_straight(Straight({  75_in,  5_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW,true,200_ms));
    path.add_intake_control(IN);
    path.add_straight(Straight({  75_in,  5_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW,false,600_ms));
    path.add_intake_control(IN_WITH_SENSE);
    path.add_straight(Straight({54_in, -5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 9999_s));
    */

    // line up for push over
    //path.add_straight(Straight({54_in, -4_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 500_ms));
    path.add_turn(MyTurn(45_deg));

    //path.add_wing_control(Wing(OPEN, FRONT));
    path.add_straight(Straight({  60_in,  8_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,400_ms));
    path.add_intake_control(OUT);
    path.add_straight(Straight({  60_in,   8_in, 0_deg}, 0_in, MOTOR_SPEED::FAST,true,1000_ms));


    path.add_straight(Straight({50_in, 5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 2000_ms));

    path.add_turn(-10_deg);#include "rev/rev.hh"
#include "path/Path.h"
#include "globals.h"
#include "api.h"

void comp_auto(std::shared_ptr<rev::TwoRotationInertialOdometry> odom, std::shared_ptr<rev::Reckless> reckless,
               std::shared_ptr<rev::CampbellTurn> turn, const IntakeSystem &intake)
{
    Path path;

    // get the bottom left ball
    path.add_straight(Straight({36_in, 0_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 9999_s));
    path.add_intake_control(IN);
    path.add_straight(Straight({43_in, -5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 9999_s));
    path.add_intake_control(IN_WITH_SENSE);

    // drop if off for Zeus to grab
    path.add_turn(MyTurn(135_deg, 700_ms));
    path.add_straight(Straight({36_in, 30_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1300_ms));
    path.add_intake_control(OUT);
    path.add_delay(400);
    path.add_intake_control(REST);
    path.add_straight(Straight({  39_in,  28_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,400_ms));

    // Go back for the second ball on the left
    path.add_turn(MyTurn(327_deg, 600_ms));
    path.add_straight(Straight({56_in, -10_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 500_ms));
    path.add_intake_control(IN);
    path.add_straight(Straight({54_in, -3_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 9999_s));
    path.add_intake_control(IN_WITH_SENSE);

    // line up for push over
    path.add_turn(MyTurn(45_deg));
    path.add_wing_control(Wing(OPEN, FRONT));
    path.add_straight(Straight({  71_in,  11_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,100_ms));
    path.add_intake_control(OUT);
    path.add_straight(Straight({  71_in,   11_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,800_ms));
    path.add_intake_control(REST);
    path.add_wing_control(Wing(CLOSE, FRONT));

    // go back to the starting point
    path.add_straight(Straight({24_in, 1_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 9999_s));
    path.add_straight(Straight({3_in, -1_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1_s));
    path.add_turn(MyTurn(-90_deg));





// intake balls
path.add_wing_control(Wing(OPEN, BACK_LEFT));
for (int i = 0; i < 4; i++) {
path.add_straight(Straight({1.5_in, 0_in, 0_deg}, 1_in, MOTOR_SPEED::MID, false, 800_ms));
path.add_straight(Straight({4.0_in, 13_in, 0_deg}, 1_in, MOTOR_SPEED::MID, false, 800_ms));
}
path.add_wing_control(Wing(CLOSE, BACK_LEFT));
path.add_wing_control(Wing(OPEN, BACK_RIGHT));

path.add_delay(200);

// go to the other side
path.add_straight(Straight({7.07_in, 25.46_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 800_ms));

path.add_straight(Straight({36.77_in, 55.15_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true));
path.add_straight(Straight({43.84_in, 62.23_in, 0_deg}, 5_in, MOTOR_SPEED::MID, true));

// open back wing as soon as robot reaches other side
path.add_straight(Straight({53.03_in, 71.42_in, 0_deg}, 4_in, MOTOR_SPEED::MID, true, 2500_ms));
path.add_wing_control(Wing(OPEN, BACK_LEFT));

path.add_straight(Straight({74.25_in, 81.32_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1000_ms));

// push the balls in

path.add_straight(Straight({91.92_in, 70.71_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 600_ms));

path.add_straight(Straight({98.99_in, 63.64_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false, 600_ms));

path.add_wing_control(Wing(CLOSE, BACK_LEFT));

for (int i = 0; i < 2; i++) {
path.add_straight(Straight({77.78_in, 77.78_in, 0_deg}, 2_in, MOTOR_SPEED::MID, false, 1200_ms));

path.add_straight(Straight({92.63_in, 71.42_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 600_ms));
path.add_straight(Straight({ 100_in,  70_in, 0_deg}, 0_in, MOTOR_SPEED::FAST,false,800_ms));
}

// go to pole
path.add_wing_control(Wing(CLOSE, BACK_RIGHT));

path.add_straight(Straight({  65_in,  79_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1_s));
path.add_turn(MyTurn(226_deg));
path.add_straight(Straight({  39_in,  48_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,2_s));


//path.add_straight(Straight({84.85_in, 63.64_in, 0_deg}, 2_in, MOTOR_SPEED::MID, true));
//path.add_straight(Straight({67.18_in, 45.96_in, 0_deg}, 4_in, MOTOR_SPEED::MID, true));

/*
path.add_intake_control(IN);
path.add_delay(200);
path.add_straight(Straight({63.64_in, 28.28_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false, 1000_ms));
path.add_intake_control(IN_WITH_SENSE);

path.add_turn(MyTurn(-45.0_deg));

path.add_straight(Straight({74.25_in, 24.75_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false));
path.add_wing_control(Wing(OPEN, FRONT));
path.add_delay(100);
path.add_straight(Straight({102.53_in, 45.96_in, 0_deg}, 0_in, MOTOR_SPEED::FAST, false, 800_ms));

path.add_intake_control(OUT);
path.add_straight(Straight({ 107_in,  44_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1.5_s));



path.add_intake_control(REST);
path.add_wing_control(Wing(CLOSE, FRONT));
*/
//path.add_straight(Straight({74.25_in, 31.82_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1500_ms));
//path.add_straight(Straight({49.50_in, 39.60_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 1500_ms));

//path.add_wing_control(Wing(OPEN, BACK_LEFT));



    path.go(reckless, turn, Wings{backWingL, backWingR, frontWings}, intake);
}
    path.add_straight(Straight({  70_in,  5_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,200_ms));
    path.add_intake_control(IN);
    path.add_straight(Straight({  70_in,   5_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1000_ms));
    path.add_intake_control(IN_WITH_SENSE);

    path.add_straight(Straight({50_in, 5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 2000_ms));
    path.add_straight(Straight({  60_in,   8_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,1000_ms));

    path.add_intake_control(OUT_SLOW);
    path.add_delay(600);
    path.add_intake_control(REST);

    /*
    path.add_straight(Straight({54_in, -5_in, 0_deg}, 0_in, MOTOR_SPEED::MID, false, 1500_ms));
    path.add_straight(Straight({  68_in,  13_in, 0_deg}, 0_in, MOTOR_SPEED::MID,true,100_ms));
    path.add_straight(Straight({  70_in,   18_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1000_ms));
    */

    path.add_intake_control(REST);
    path.add_wing_control(Wing(CLOSE, FRONT));





    // go back to the starting point
    path.add_straight(Straight({24_in, 1_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 9999_s));
    path.add_straight(Straight({3_in, -1_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1_s));
    path.add_turn(MyTurn(-90_deg, 800_ms));





// intake balls
path.add_wing_control(Wing(OPEN, BACK_LEFT));
for (int i = 0; i < 6; i++) {
path.add_straight(Straight({1.5_in, 0_in, 0_deg}, 1_in, MOTOR_SPEED::MID, false, 800_ms));
path.add_straight(Straight({4.0_in, 13_in, 0_deg}, 1_in, MOTOR_SPEED::MID, false, 800_ms));
}
path.add_wing_control(Wing(CLOSE, BACK_LEFT));
path.add_wing_control(Wing(OPEN, BACK_RIGHT));

path.add_delay(200);

// go to the other side
path.add_straight(Straight({7.07_in, 25.46_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 800_ms));

path.add_straight(Straight({36.77_in, 55.15_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true));
path.add_straight(Straight({43.84_in, 62.23_in, 0_deg}, 5_in, MOTOR_SPEED::MID, true));

// open back wing as soon as robot reaches other side
path.add_straight(Straight({53.03_in, 71.42_in, 0_deg}, 4_in, MOTOR_SPEED::MID, true, 2500_ms));
path.add_wing_control(Wing(OPEN, BACK_LEFT));

path.add_straight(Straight({74.25_in, 81.32_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 1000_ms));

// push the balls in

path.add_straight(Straight({91.92_in, 70.71_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 600_ms));

path.add_straight(Straight({98.99_in, 63.64_in, 0_deg}, 0_in, MOTOR_SPEED::SLOW, false, 600_ms));

path.add_wing_control(Wing(CLOSE, BACK_LEFT));

for (int i = 0; i < 2; i++) {
    path.add_straight(Straight({77.78_in, 77.78_in, 0_deg}, 2_in, MOTOR_SPEED::MID, false, 1200_ms));

    path.add_straight(Straight({94.63_in, 73.42_in, 0_deg}, 0_in, MOTOR_SPEED::MID, true, 600_ms));
    path.add_straight(Straight({ 100_in,  70_in, 0_deg}, 0_in, MOTOR_SPEED::FAST,true,800_ms));
}

// go to pole
path.add_wing_control(Wing(CLOSE, BACK_RIGHT));

path.add_straight(Straight({  65_in,  79_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,1_s));
path.add_turn(MyTurn(226_deg));
path.add_straight(Straight({  32_in,  43_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,2_s));

path.add_wing_control(Wing(OPEN, BACK_RIGHT));

//path.add_straight(Straight({  33_in,  42_in, 0_deg}, 0_in, MOTOR_SPEED::MID,false,0.7_s));

path.go(reckless, turn, Wings{backWingL, backWingR, frontWings}, intake);
}