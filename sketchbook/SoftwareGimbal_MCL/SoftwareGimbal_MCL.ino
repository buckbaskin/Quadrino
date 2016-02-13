#include <MatrixMath.h>
#include <rate.h>
#include "IMU_Types.h"
#include "IMU.h"
#include <math.h>

Rate imu_rate(10.0); // rate to poll IMU, hopefully will make this
Rate control_rate(50.0); // rate to update control feedback, probably won't make 100hz

short counter = 0;

Vector3 accel;
Vector3 gyro;
Vector3 mag;

Vector3 accel_bias;
Vector3 gyro_bias;
Vector3 mag_bias;

Vector3 twist = {0.0,0.0,0.0};

int particle_count = 10;
RotMatrix particles[10];

void init_MCL_particles(RotMatrix * particles, int num_particles);
void evolve_particle(RotMatrix * particle, Vector3 ctrl, float dt);
void motion_model(RotMatrix* particles, int num_particles, Vector3 ctrl, float dt);
void update_control(RotMatrix* particles, int num_particles);
void filter_particles(RotMatrix* particles, int particle_count);
float randomly(float mu, float sigma);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Software Gimbal Example");
  Serial.println("");
  pinMode(13, OUTPUT);
  /* Initialise the sensors */
  init_sensors(false);

  init_MCL_particles((RotMatrix*) particles, particle_count);

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
  if (control_rate.q()) {
    motion_model((RotMatrix*) particles, particle_count, twist, 1.0/control_rate.hz());
    update_control((RotMatrix*) particles, particle_count, 1.0/control_rate.hz());
    counter++;
    if (counter % 2) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    }
    poll_imu(&accel, &gyro, &mag);
    filter_particles((RotMatrix*) particles, particle_count);
  }
}

void motion_model(RotMatrix* particles, int num_particles, Vector3 ctrl, float dt) {
  for (int i = 0; i < num_particles; i++) {
    evolve_particle(particles+i, ctrl, dt);
  }
}

void evolve_particle(RotMatrix * particle, Vector3 ctrl, float dt) {
  RotMatrix temp;
  ctrl.x *= dt;
  ctrl.x += randomly(0.0, ctrl.x+.05);
  ctrl.y *= dt;
  ctrl.y += randomly(0.0, ctrl.y+.05);
  ctrl.z *= dt;
  ctrl.z += randomly(0.0, ctrl.z+.05);
  temp[0][0] = cos(ctrl.z)*cos(ctrl.y);
  temp[0][1] = sin(ctrl.z)*cos(ctrl.y);
  temp[0][2] = -sin(ctrl.y);
  temp[1][0] = sin(ctrl.z)*cos(ctrl.x)+cos(ctrl.z)*sin(ctrl.y)*sin(ctrl.x);
  temp[1][1] = cos(ctrl.z)*cos(ctrl.x)+sin(ctrl.z)*sin(ctrl.y)*sin(ctrl.x);
  temp[1][2] = cos(ctrl.y)*sin(ctrl.x);
  temp[2][0] = sin(ctrl.y)*sin(ctrl.x)+cos(ctrl.z)*sin(ctrl.y)*cos(ctrl.x);
  temp[2][1] = -cos(ctrl.z)*sin(ctrl.x);
  temp[2][2] = cos(ctrl.y)*cos(ctrl.x);
  Matrix.Multiply((float*) temp, (float*) *particle, 3,3,3, (float*) *particle);
}

void init_MCL_particles(RotMatrix * particles, int num_particles) {
  for (int i = 0; i < num_particles; i++) {
    (*(particles+i))[0][0] = 1;
    (*(particles+i))[0][1] = 0;
    (*(particles+i))[0][2] = 0;
    (*(particles+i))[1][0] = 0;
    (*(particles+i))[1][1] = 1;
    (*(particles+i))[1][2] = 0;
    (*(particles+i))[2][0] = 0;
    (*(particles+i))[2][1] = 0;
    (*(particles+i))[2][2] = 1;
  }
}

void update_control(RotMatrix* particles, int num_particles, float dt) {
  // average the particles, and then make a control correction to level
  // PID?
}

float randomly(float mu, float sigma) {
  float u1 = ((float) random(0,1000))/(1000.0);
  float u2 = ((float) random(0,1000))/(1000.0);
  if (u1 > u2) {
    return mu+sigma*sqrt(-2*log(u1))*cos(2*3.14159*u2);
  } else {
    return mu+sigma*sqrt(-2*log(u1))*sin(2*3.14159*u2);
  }
}

void filter_particles((RotMatrix*) particles, particle_count) {
  for (int i = 0; i < num_particles; i++) {
    (*(particles+i))
  }
}

