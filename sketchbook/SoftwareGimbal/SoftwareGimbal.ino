#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"
#include "IMU.h"

// Rate slow(1.0); // do something on a slow count
Rate imu_rate(1.0); // rate to poll IMU, hopefully will make this
// Rate control_rate(100.0); // rate to update control feedback, probably won't make 100hz

int _pin = 13;
int counter = 0;

Vector3 accel;
Vector3 gyro;
Vector3 mag;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Software Gimbal Example");
  Serial.println("");
  pinMode(_pin, OUTPUT);
  /* Initialise the sensors */
  init_sensors(false);

  calc_bias(&accel_bias, &gyro_bias, &mag_bias);
  printVec(&accel);
  Serial.print(" m/s2 |");
  printVec(&gyro);
  Serial.print(" rad/s |");
  printVec(&mag); 
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (imu_rate.sleep()) {
    counter++;
    if (counter % 2) {
      digitalWrite(_pin, LOW);
    } else {
      digitalWrite(_pin, HIGH);
    }
    poll_imu(&accel, &gyro, &mag);
    //printVec(&accel);
    //Serial.print(" m/s2 |");
    //printVec(&gyro);
    //Serial.print(" rad/s |");
    //printVec(&mag); 
    //Serial.println("");
    // filter sensor update
    delay(100);
  }
}

