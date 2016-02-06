/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int counter = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  while(!Serial);
  Serial.begin(9600);
  Serial.println("Begin...");
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    Serial.print("rcvd chars: >");
    digitalWrite(led, HIGH);
    char ch = Serial.read();
    while(ch != '\n' && ch != '\xff' && ch != '\r') {
      Serial.print(ch);
      // delay(1000);
      ch = Serial.read();
    }
    counter = 0;
    while(ch == '\n' || ch == '\xff' || ch == '\r') {
      ch = Serial.read();
      if((counter++) > 1000) {
        break;
      }
    }
    digitalWrite(led, LOW);
    Serial.println("< and send end");
  }
}
