#ifndef MCLTYPES_h
#define MCLTYPES_h

struct Vec3 {
  float x;
  float y;
  float z;
};
typedef struct Vec3 Vec3;

typedef struct RotMatrix {
  /*
    x y z
  x . . .
  y . . .
  z . . .
  */
  struct Vec3 x;
  struct Vec3 y;
  struct Vec3 z;
} RotMatrix;

typedef struct State {
  struct Vec3 position;
  struct RotMatrix orientation;
  struct Vec3 linear_vel;
  struct Vec3 angular_vel;
} State;

#endif
