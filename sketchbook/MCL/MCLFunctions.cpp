#include "MCLFunctions.h"

int randomStartState(State * to_fill) {
  randomVec3(&(to_fill -> position));
  randomVec3(&(to_fill -> linear_vel));
  randomVec3(&(to_fill -> angular_vel));
  return 1;
}

int randomRotMatrix(RotMatrix * to_fill) {
  randomVec3(&(to_fill -> x));
  to_fill -> x.x = 1.0;
  randomVec3(&(to_fill -> y));
  to_fill -> y.y = 1.0;
  randomVec3(&(to_fill -> z));
  to_fill -> z.z = 1.0;
  return 1;
}

int randomVec3(Vec3 * to_fill) {
  to_fill -> x = 0;
  to_fill -> y = 0;
  to_fill -> z = 0;
  return 1;
}
