#ifndef IMU_H
#define IMU_H

#include "Arduino.h"
#include "IMU_Types.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

void initSensors();

#endif
