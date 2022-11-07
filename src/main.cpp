#include <Arduino.h>
int Distance = 0;  // Record the number of steps we've taken

void setup() {               
  pinMode(26, OUTPUT);    
  pinMode(27, OUTPUT);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
}

void loop() {
  digitalWrite(27, HIGH);
  delayMicroseconds(75);         
  digitalWrite(27, LOW);
  delayMicroseconds(75);
  Distance = Distance + 1;   // record this step
 
  // Check to see if we are at the end of our move
  if (Distance == 5376)
  {
    // We are! Reverse direction (invert DIR signal)
    //if (digitalRead(26) == LOW)
    //{
    //  digitalWrite(26, HIGH);
    //}
    //else
    //{
    //  digitalWrite(26, LOW);
    //}
    // Reset our distance back to zero since we're
    // starting a new move
    Distance = 0;
    // Now pause for half a second
    delay(300);
  }
}