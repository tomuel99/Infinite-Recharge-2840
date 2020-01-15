/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <Robot.h>
#include <iostream>
#include <memory>
#include <string>

#include <SageFunctions.h>
#include <cameraServer/CameraServer.h>
#include <frc/IterativeRobot.h>
#include <frc/Joystick.h>
#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/Timer.h>
#include <frc/Spark.h>
#include <frc/Encoder.h>
#include <frc/WPILib.h>
#include <OI.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/LiveWindow/LiveWindow.h>
#include "networktables/NetworkTable.h"
#include "networkTables/NetworkTableInstance.h"
//#include "PigeonIMU.h"
//#include <ctre/Phoenix.h>
#include "rev/SparkMax.h"
//#include <math.h>

frc::Joystick stick{0};
rev::SparkMax frontLeft{0}, frontRight{1}, backLeft{2}, backRight{3}, intake{4}, internal{5}, shooter{6}, panel{7};
frc::RobotDrive myRobot{frontLeft, backLeft, backRight, frontRight};
frc::Timer timer;

double speed, turn, sensitivity = 1.0;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //frc::SmartDashboard::PutNumber("Timer", timer.Get());
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  //myRobot.ArcadeDrive(1.0, 0.0)
  frc::SmartDashboard::PutNumber("Timer", timer.Get());
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    timer.Reset();
    timer.Start();
    // Custom Auto goes here
  } else {
    timer.Reset();
    timer.Start();
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    if (timer.Get() < 3) {
      myRobot.ArcadeDrive(-0.5, 0.0);
    }
    else {
      myRobot.ArcadeDrive(0.0, 0.0);
    }
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  if (stick.GetPOV(0)) {//increase sensitivity by pressing up on D pad
    sensitivity += 0.01;
  }
  else if (stick.GetPOV(180)) {//decrease sensitivity by pressing down on D pad
    sensitivity -= 0.01;
  }
  if (sensitivity > 1.0) {//max out sensitivity at 1.0
    sensitivity = 1.0;
  }
  else if (sensitivity < 0.1) {//minimum sensitivity = 0.1
    sensitivity = 0.1;
  }
  turn = -stick.GetRawAxis(4)*sensitivity; //turn by using right stick
  speed = stick.GetRawAxis(1)*sensitivity; //throttle on left stick
  myRobot.ArcadeDrive(speed, turn);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
