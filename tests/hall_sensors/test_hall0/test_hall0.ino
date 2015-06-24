/*
 Hall Effect Switch - TEST 1
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when one of two Hall Effect Sensor attached to input pins
 is triggered by a magnet. The complete sensors status is written
 to the serial console.
 
 Hall effect sensor used is the A1120EUA from Allegro Microsystems
 
 This example code is written starting by the following tutorial:
 http://www.hobbytronics.co.uk/arduino-tutorial8-hall-effect
 
 and it is in the public domain:
 http://www.fpiantini.it/
 
*/

// **********************************************************
// CONSTANTS --------------------------------

// input used as hall sensor inputs
const int vccPin = 7;
const int hallPin = 8;

// output used to drive led
const int ledPin =  13;

// VARIABLES --------------------------------
// hall sensors state
int hallState;
int newHallState;

// **********************************************************

// * * * * * * * * * * * * * * * * * * * * * * * * *
void setup() {

  // initialize serial console and print banner
  Serial.begin(9600); // This sets up a serial connection, 9.6 kbts/s.
  Serial.println("Hall sensor TEST0, by F. Piantini, 20140111");

  // initialize the LED pin as an output and turns it off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  //pinMode(vccPin, OUTPUT);
  //digitalWrite(vccPin, LOW); 
  pinMode(vccPin, INPUT);

  // initialize the hall effect sensor pins as inputs
  // and initialize status
  pinMode(hallPin, INPUT);
  hallState = -1;
  newHallState = LOW;

}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void loop() {
  int statChanged = false;
  int hall_active = false;
  
  // update the state of the hall effect sensors

  //digitalWrite(vccPin, HIGH); 
  //delay(1);
  newHallState = digitalRead(hallPin);
  //digitalWrite(vccPin, LOW); 
  //delay(1);

  if (newHallState != hallState) {
    hallState = newHallState;
    statChanged = true;
  }
  if (hallState == LOW)
    hall_active = true;
  
  if (statChanged == true) {
    updateLed(hall_active);
    printStatus();
  }
}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void printStatus() {
  Serial.print("Hall sensor status changed:  ");
  Serial.print(hallState);
  Serial.print("\n");
}

  
// * * * * * * * * * * * * * * * * * * * * * * * * *
void updateLed(int oneActive) {  
  if (oneActive == true) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}




