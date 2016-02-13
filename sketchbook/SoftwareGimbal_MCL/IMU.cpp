#include "IMU.h"


Adafruit_9DOF                 dof    = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accelu = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   magu   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyrou  = Adafruit_L3GD20_Unified(20);

//Vector3 accel_bias = {0,0,0};
//Vector3 gyro_bias = {0,0,0};
//Vector3 mag_bias = {0,0,0};

void init_sensors(bool debug)
{
  gyrou.enableAutoRange(true);
  
  sensor_t sensor;
  int meme = 0;
  if(!accelu.begin()) {
    meme++;
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("No LSM303-accel detected ... Check your wiring!");
  } else if (debug) {
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
  } else if (debug) {
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

  if (!gyrou.begin()) { // ignore blocking call?
    meme++;
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("No L3GD20 detected by default ... (maybe) Check your wiring!");
  } else if (debug) {
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
  sensors_event_t event;
  accelu.getEvent(&event);
  accel -> x = event.acceleration.x;
  accel -> y = event.acceleration.y;
  accel -> z = event.acceleration.z;
  gyrou.getEvent(&event);
  gyro -> x = event.gyro.x;
  gyro -> y = event.gyro.y;
  gyro -> z = event.gyro.z;
  magu.getEvent(&event);
  mag -> x = event.magnetic.x;
  mag -> y = event.magnetic.y;
  mag -> z = event.magnetic.z;
  return 1;
}

int calc_bias(Vector3* accel, Vector3* gyro, Vector3* mag) {
  Serial.println("Hold still on a level surface, checking for bias");
  delay(1000);
  accel -> x = 0;
  accel -> y = 0;
  accel -> z = 0;
  gyro -> x = 0;
  gyro -> y = 0;
  gyro -> z = 0;
  mag -> x = 0;
  mag -> y = 0;
  mag -> z = 0;

  sensors_event_t event;
  
  for (int i = 0; i < 1000; i++) {
    accelu.getEvent(&event);
    accel -> x += event.acceleration.x;
    accel -> y += event.acceleration.y;
    accel -> z += event.acceleration.z - 9.81;
    gyrou.getEvent(&event);
    gyro -> x += event.gyro.x;
    gyro -> y += event.gyro.y;
    gyro -> z += event.gyro.z;
    magu.getEvent(&event);
    mag -> x += event.magnetic.x;
    mag -> y += event.magnetic.y;
    mag -> z += event.magnetic.z;
    if(i%100 == 0) {
      Serial.println(10-i/100);
    }
    delay(5);
  }
  accel -> x = accel -> x / 1000.0;
  accel -> y = accel -> y / 1000.0;
  accel -> z = accel -> z / 1000.0;
  gyro -> x = gyro -> x / 1000.0;
  gyro -> y = gyro -> y / 1000.0;
  gyro -> z = gyro -> z / 1000.0;
  mag -> x = mag -> x / 1000.0;
  mag -> y = mag -> x / 1000.0;
  mag -> z = mag -> x / 1000.0;
  Serial.println("Done checking for bias");
  return 1;
}

extern Adafruit_9DOF dof;
extern Adafruit_LSM303_Accel_Unified accelu;
extern Adafruit_LSM303_Mag_Unified magu;
extern Adafruit_L3GD20_Unified gyrou;

//extern Vector3 accel_bias;
//extern Vector3 gyro_bias;
//extern Vector3 mag_bias;
