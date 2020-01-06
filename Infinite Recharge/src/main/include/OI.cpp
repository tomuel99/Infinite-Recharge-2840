#include <OI.h>
#include <SageFunctions.h>
#include <frc/Joystick.h>

frc::Joystick stick{0}

double axis(int axisNum) {
    return stick.GetRawAxis(axisNum);
}