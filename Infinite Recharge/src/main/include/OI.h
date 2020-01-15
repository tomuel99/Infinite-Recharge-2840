#ifndef OI_H
#define OI_H
// #pragma once
#include <frc/Joystick.h>
#include "SageFunctions.h"

class OI {
 public:
  frc::Joystick stick{0};
  double axis();
  OI();
};

#endif
