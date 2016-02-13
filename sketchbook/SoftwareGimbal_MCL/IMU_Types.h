#ifndef IMU_TYPES_H
#define IMU_TYPES_H

#include "Arduino.h"

struct Vector3 {
  float x;
  float y;
  float z;
};
typedef struct Vector3  Vector3;

//struct RotMatrix {
//  Vector3 x;
//  Vector3 y;
//  Vector3 z;
//};

typedef float RotMatrix[3][3];

struct Measurement {
  Vector3 accel;
  Vector3 gyro;
  Vector3 mag;
};
typedef struct Measurement Measurement;

// typedef float Covariance[9][9];
// typedef float BigMatrix[9][9];

void printVec(Vector3 * input);

#endif
