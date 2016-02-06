/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

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
    Serial.print("rcvd chars: ");
    char ch = Serial.read();
    while(ch != '\n') {
      Serial.print(ch);
      ch = Serial.read();
    }
    Serial.println(" and newline char");
  }
}
