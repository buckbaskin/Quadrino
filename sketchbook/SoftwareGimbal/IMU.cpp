#include "IMU.h"


Adafruit_9DOF                 dof    = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accelu = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   magu   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyrou  = Adafruit_L3GD20_Unified(20);


void init_sensors()
{
  gyrou.enableAutoRange(true);
  
  sensor_t sensor;
  int meme = 0;
  if(!accelu.begin()) {
    meme++;
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("No LSM303-accel detected ... Check your wiring!");
  } else {
    accelu.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
    Serial.println("------------------------------------");
    Serial.println("");
  }
  
  if(!magu.begin()) {
    meme++;
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("No LSM303-mag detected ... Check your wiring!");
  } else {
    magu.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
    Serial.println("------------------------------------");
    Serial.println("");
  }

  if (true || !gyrou.begin()) { // ignore blocking call?
    meme++;
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("No L3GD20 detected by default ... (maybe) Check your wiring!");
  } else {
    gyrou.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" rad/s");
    Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" rad/s");
    Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" rad/s");  
    Serial.println("------------------------------------");
    Serial.println("");
  }
  if (meme == 3) {
    Serial.println("");
    Serial.println("");
    Serial.println("No sensors live...");
    Serial.println("");
    Serial.println("");
  } else {
    Serial.println("Some sensors live...");
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
extern Adafruit_LSM303_Accel_Unified accelu;
extern Adafruit_LSM303_Mag_Unified magu;
extern Adafruit_L3GD20_Unified gyrou;
