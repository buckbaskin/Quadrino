#ifndef IMU_TYPES_H
#define IMU_TYPES_H

#include "Arduino.h"

struct Vector3 {
  float x;
  float y;
  float z;
};

typedef struct Vector3  Vector3;

void printVec(Vector3 * input);

#endif
