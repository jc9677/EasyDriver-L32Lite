#include <Arduino.h>
#include <AccelStepper.h>

// Define the stepper and the pins it will use
AccelStepper stepper1(AccelStepper::DRIVER, 27, 26);

// Define our three input button pins
#define  LEFT_PIN  4
#define  STOP_PIN  3
#define  RIGHT_PIN 2

// Define our analog pot input pin
#define  SPEED_PIN 0

// Define our maximum and minimum speed in steps per second (scale pot to these)
#define  MAX_SPEED 3600
#define  MIN_SPEED 0.1

void setup() {
  analogReadResolution(10);
  Serial.begin(115200);
  // The only AccelStepper value we have to set here is the max speeed, which is higher than we'll ever go
  stepper1.setMaxSpeed(10000.0);
 
  // Set up the three button inputs, with pullups
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
}

void loop() {
  static float current_speed = 0.0;         // Holds current motor speed in steps/second
  static int analog_read_counter = 1000;    // Counts down to 0 to fire analog read
  static char sign = 0;                     // Holds -1, 1 or 0 to turn the motor on/off and control direction
  static int analog_value = 0;              // Holds raw analog value.
  

 
  // If a switch is pushed down (low), set the sign value appropriately
/*   if (digitalRead(LEFT_PIN) == 0) {
    sign = 1;
  }
  else if (digitalRead(RIGHT_PIN) == 0) {    
    sign = -1;
  }
  else if (digitalRead(STOP_PIN) == 0) {
    sign = 0;
  }
 */
  // We only want to read the pot every so often (because it takes a long time we don't
  // want to do it every time through the main loop).  
  if (analog_read_counter > 0) {
    analog_read_counter--;
  }
  else {
    analog_read_counter = 300;
    // Now read the pot (from 0 to 1023)
    analog_value = analogRead(SPEED_PIN);
    Serial.print("Analog: ");
    Serial.print(analog_value);
    // Give the stepper a chance to step if it needs to
    stepper1.runSpeed();
    //  And scale the pot's value from min to max speeds
    if (analog_value > 515) {
      sign = 1;
    }
    if (analog_value < 509) {
      sign = -1;
    }
      
    current_speed = ((((analog_value-512)/512.0) * (MAX_SPEED - MIN_SPEED)) + MIN_SPEED);
    Serial.print("    Scaled: ");
    Serial.print(current_speed);
    Serial.println("");
    // Update the stepper to run at this new speed
    stepper1.setSpeed(current_speed);
  }

  // This will run the stepper at a constant speed
  stepper1.runSpeed();
}