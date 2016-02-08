#include <MatrixMath.h>
#include "MCLTypes.h"
#include "MCLFunctions.h"

int state_length = 5;
struct State * samples;

void setup() {
  samples = new State[5];
  for(int i = 0; i < state_length; i++) {
    randomStartState(&samples[i]);
  }
}

void loop() {
    
}
