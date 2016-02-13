#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"
// #include "IMU.h"

Rate slow(1.0); // do something on a slow count
Rate imu_rate(5.0); // rate to poll IMU, hopefully will make this
Rate control_rate(100.0); // rate to update control feedback, probably won't make 100hz

int _pin = 13;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Software Gimbal Example");
  Serial.println("");
  pinMode(_pin, OUTPUT);
  /* Initialise the sensors */
  // initSensors();
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
  if (slow.q()) {
    counter++;
    if (counter % 2) {
      digitalWrite(_pin, LOW);
    } else {
      digitalWrite(_pin, HIGH);
    }
  }
}

