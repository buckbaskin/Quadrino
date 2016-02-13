struct Vec3 {
  float x;
  float y;
  float z;
};

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Vec3 v;
  v.x = 1;
  v.y = 2;
  v.z = 3;

  float* pntr = &v.x;
  Serial.println(*pntr);
  Serial.println(*(pntr+1));
  Serial.println(*(pntr+2));
}

void loop() {
  // put your main code here, to run repeatedly:

}
