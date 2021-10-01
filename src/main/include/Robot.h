// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <ElapsedTimer.hpp>

class Robot : public frc::TimedRobot
{
public:
    enum class CATAPULT_STATE
    {
        PRIMED = 0,
        FIRING = 1,
        WINDING = 2,
        UNWINDING = 3
    };

    void RobotInit() override;
    void RobotPeriodic() override;

    void AutonomousInit() override;
    void AutonomousPeriodic() override;

    void TeleopInit() override;
    void TeleopPeriodic() override;

    void DisabledInit() override;
    void DisabledPeriodic() override;

    void TestInit() override;
    void TestPeriodic() override;

private:
    // Intake
    TalonSRX intake{1};

    // Catapult
    TalonSRX cat_winch{5};
    TalonSRX cat_winch_inv{6};
    frc::Solenoid cat_solenoid{0};
    frc::DigitalInput cat_limit_switch{0};
    CATAPULT_STATE cat_state = CATAPULT_STATE::WINDING;

    const int TALON_ENCODER_MULTIPLER = 4;
    const int ENCODER_TICKS = 128;
    const int APPROXIMATE_WINCH_ROTATION = TALON_ENCODER_MULTIPLER * ENCODER_TICKS;

    const double FIRING_DELAY = 1.5;
    ElapsedTimer firing_timer;

    frc::Compressor compressor{0};
    frc::Joystick joystick{0};
};
