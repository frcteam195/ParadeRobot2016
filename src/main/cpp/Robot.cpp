// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/livewindow/LiveWindow.h>
#include <iostream>

using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

void Robot::RobotInit()
{
    frc::LiveWindow::DisableAllTelemetry();
    frc::LiveWindow::SetEnabled(false);

    cat_winch.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    cat_winch.SetSensorPhase(true);
    cat_winch.SetInverted(InvertType::None);
    cat_winch.Set(ControlMode::PercentOutput, 0);
    SupplyCurrentLimitConfiguration limit(true, 35, 0, 0);
    cat_winch.ConfigSupplyCurrentLimit(limit);

    std::cout << "Catapult State Defaults to WINDING" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
    cat_state = CATAPULT_STATE::WINDING;
}

void Robot::TeleopPeriodic()
{
    switch (cat_state)
    {
    case CATAPULT_STATE::WINDING:

        cat_solenoid.Set(false);
        cat_winch.Set(ControlMode::PercentOutput, 0.8);

        if (!cat_limit_switch.Get())
        {
            cat_winch.SetSelectedSensorPosition(0);
            cat_state = CATAPULT_STATE::UNWINDING;
            std::cout << "Catapult Transitioning to UNWINDING" << std::endl;
        }

        break;

    case CATAPULT_STATE::UNWINDING:
        cat_solenoid.Set(false);
        cat_winch.Set(ControlMode::PercentOutput, -1.0);
        std::cout << "Pos: " << cat_winch.GetSelectedSensorPosition() << std::endl;
        if (cat_winch.GetSelectedSensorPosition() < -1 * WINCH_ROTATION)
        {
            cat_state = CATAPULT_STATE::PRIMED;
            std::cout << "Catapult Transitioning to PRIMED" << std::endl;
        }

        break;

    case CATAPULT_STATE::PRIMED:
        cat_solenoid.Set(false);
        cat_winch.Set(ControlMode::PercentOutput, 0);

        // Input
        if (joystick.GetRawButton(1))
        {
            firing_timer.start();
            cat_state = CATAPULT_STATE::FIRING;
            std::cout << "Catapult Transitioning to FIRING" << std::endl;
        }
        break;

    case CATAPULT_STATE::FIRING:
        cat_solenoid.Set(true);

        // Wait some amount of time.
        if (firing_timer.hasElapsed() > FIRING_DELAY)
        {
            cat_state = CATAPULT_STATE::WINDING;
            std::cout << "Catapult Transitioning to WINDING" << std::endl;
        }

        break;

    default:
        std::cout << "Warning: Uknown Catapult State!" << std::endl;
        break;
    }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
