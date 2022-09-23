#include "ElapsedTimer.hpp"

ElapsedTimer::ElapsedTimer() {}

void ElapsedTimer::start() {
    startTime = frc::Timer::GetFPGATimestamp().value();
}

double ElapsedTimer::hasElapsed() {
    return frc::Timer::GetFPGATimestamp().value() - startTime;
}
