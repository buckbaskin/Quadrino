#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"
#include "IMU.h"

// Rate slow(1.0); // do something on a slow count
Rate imu_rate(5.0); // rate to poll IMU, hopefully will make this
// Rate control_rate(100.0); // rate to update control feedback, probably won't make 100hz

int _pin = 13;
int counter = 0;

Vector3 accel;
Vector3 gyro;
Vector3 mag;

Vector3 accel_bias;
Vector3 gyro_bias;
Vector3 mag_bias;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Software Gimbal Example");
  Serial.println("");
  pinMode(_pin, OUTPUT);
  /* Initialise the sensors */
  init_sensors(false);

  calc_bias(&accel_bias, &gyro_bias, &mag_bias);
  printVec(&accel_bias);
  Serial.print(" m/s2 | ");
  printVec(&gyro_bias);
  Serial.print(" rad/s | ");
  printVec(&mag_bias); 
  Serial.println(" uTesla");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (imu_rate.q()) {
    counter++;
    if (counter % 2) {
      digitalWrite(_pin, LOW);
    } else {
      digitalWrite(_pin, HIGH);
    }
    poll_imu(&accel, &gyro, &mag);
  }
}

