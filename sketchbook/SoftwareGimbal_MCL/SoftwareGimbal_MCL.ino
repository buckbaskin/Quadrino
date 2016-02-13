#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"
#include "IMU.h"

// Rate slow(1.0); // do something on a slow count
float hz = 5.0;
Rate imu_rate(hz); // rate to poll IMU, hopefully will make this
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

void EKF(RotMatrix * mean, BigMatrix * covar, Vector3 * ctrl, Measurement * mea) {
  BigMatrix g;
  setG((float*)&g, ctrl, 1.0/hz);
}

void setG(float * g, Vector3 * ctrl, float dt) {
  for(int i = 0; i < 81; i++) {
    *(g+i) = 0.0;
  }
  // g[i][j], for xs
  *(g+0*9+0) = cos((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+0*9+1) = sin((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+0*9+2) = sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
  *(g+1*9+0) = sin((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+1*9+1) = cos((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+1*9+1) = -cos((ctrl -> z) * dt)*sin((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+2*9+0) = -sin((ctrl -> y) * dt);
  *(g+2*9+1) = cos((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+2*9+2) = cos((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
  // g[i][j], for ys
  *(g+3*9+3) = cos((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+3*9+4) = sin((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+3*9+5) = sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
  *(g+4*9+3) = sin((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+4*9+4) = cos((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+4*9+5) = -cos((ctrl -> z) * dt)*sin((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+5*9+3) = -sin((ctrl -> y) * dt);
  *(g+5*9+4) = cos((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+5*9+5) = cos((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
  // g[i][j], for zs
  *(g+6*9+6) = cos((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+6*9+7) = sin((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+6*9+8) = sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt) +  cos((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
  *(g+7*9+6) = sin((ctrl -> z) * dt)*cos((ctrl -> y) * dt);
  *(g+7*9+7) = cos((ctrl -> z) * dt)*cos((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+7*9+8) = -cos((ctrl -> z) * dt)*sin((ctrl -> x) * dt) +  sin((ctrl -> z) * dt)*sin((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+8*9+6) = -sin((ctrl -> y) * dt);
  *(g+8*9+7) = cos((ctrl -> y) * dt)*sin((ctrl -> x) * dt);
  *(g+8*9+8) = cos((ctrl -> y) * dt)*cos((ctrl -> x) * dt);
}

