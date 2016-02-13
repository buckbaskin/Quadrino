#include "IMU_Types.h"

void printVec(Vector3 * input) {
  Serial.print(input -> x); Serial.print(",");
  Serial.print(input -> y); Serial.print(",");
  Serial.print(input -> z);
}
