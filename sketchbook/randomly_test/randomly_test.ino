float randomly(float mu, float sigma) {
  float u1 = ((float) random(0,1000))/(1000.0);
  float u2 = ((float) random(0,1000))/(1000.0);
  if (u1 > u2) {
    return mu+sigma*sqrt(-2*log(u1))*cos(2*3.14159*u2);
  } else {
    return mu+sigma*sqrt(-2*log(u1))*sin(2*3.14159*u2);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(randomly(0,1));
  // Serial.println(",");
  delay(500);
}
