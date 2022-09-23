// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <ctre/Phoenix.h>
#include <ElapsedTimer.hpp>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/Joystick.h>
#include <frc/Compressor.h>


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
    // Catapult
    TalonSRX cat_winch{6};
    frc::Solenoid cat_solenoid{frc::PneumaticsModuleType::CTREPCM, 1};
    frc::DigitalInput cat_limit_switch{9};
    CATAPULT_STATE cat_state = CATAPULT_STATE::WINDING;

    const int ENCODER_TICKS_PER_REV = 4096;
    const int WINCH_ROTATION = ENCODER_TICKS_PER_REV;

    const double FIRING_DELAY = 1.5;
    ElapsedTimer firing_timer;

    frc::Compressor compressor{frc::PneumaticsModuleType::CTREPCM};
    frc::Joystick joystick{0};
};
