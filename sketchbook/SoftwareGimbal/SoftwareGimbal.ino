#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"

Rate imu_rate(10.0); // rate to poll IMU, hopefully will make this
Rate control_rate(100.0); // rate to update control feedback, probably won't make 100hz

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (control_rate.q()) {
    // control_update();
    // filter motion update();
  }
  if (imu_rate.q()) {
    // poll_imu(accel struct*, gyro struct*, msg struct*)
    // filter sensor update();
  }
}

