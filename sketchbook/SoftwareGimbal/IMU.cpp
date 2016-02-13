#include "IMU.h"


Adafruit_9DOF                 dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accelu = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   magu   = Adafruit_LSM303_Mag_Unified(30302);

void init_sensors()
{
  if(!accelu.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("No LSM303-accel detected ... Check your wiring!");
  }
  if(!magu.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("No LSM303-mag detected ... Check your wiring!");
  }
}

int poll_imu(Vector3* accel, Vector3* gyro, Vector3* mag) {
  accel -> x = !(accel -> x);
  accel -> y = 0;
  accel -> z = 0;
  gyro -> x = 0;
  gyro -> y = !(gyro -> y);
  gyro -> z = 0;
  mag -> x = 0;
  mag -> y = 0;
  mag -> z = !(mag -> z);

  return 1;
}

extern Adafruit_9DOF dof;
extern Adafruit_LSM303_Accel_Unified accel;
extern Adafruit_LSM303_Mag_Unified mag;
