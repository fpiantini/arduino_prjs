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

// Number of hall effect sensors
const int numSens = 2;

// input used as hall sensor inputs
const int hallPins[numSens] = {8, 7};

// output used to drive led
const int ledPin =  13;

// VARIABLES --------------------------------
// hall sensors state
int hallState[numSens];
int newHallState[numSens];
int cont;

// **********************************************************

// * * * * * * * * * * * * * * * * * * * * * * * * *
void setup() {

  // initialize serial console and print banner
  Serial.begin(9600); // This sets up a serial connection, 9.6 kbts/s.
  Serial.println("Hall sensor TEST1, by F. Piantini, 20140111");

  // initialize the LED pin as an output and turns it off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  // initialize the hall effect sensor pins as inputs
  // and initialize status
  for (cont = 0; cont < numSens; cont++) {
    pinMode(hallPins[cont], INPUT);
    hallState[cont] = -1;
    newHallState[cont] = LOW;
  }

}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void loop() {
  int atLeastOneActive = false;
  int statChanged = false;
  
  // update the state of the hall effect sensors
  for (cont = 0; cont < numSens; cont++) {
    newHallState[cont] = digitalRead(hallPins[cont]);
    if (newHallState[cont] != hallState[cont]) {
      hallState[cont] = newHallState[cont];
      statChanged = true;
    }
    if (hallState[cont] == LOW)
      atLeastOneActive = true;
  }
  
  if (statChanged == true) {
    updateLed(atLeastOneActive);
    printStatus();
  }
}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void printStatus() {
  Serial.print("Hall sensor status changed:  ");
  for (cont = 0; cont < numSens; cont++) {
    Serial.print(hallState[cont]);
    if (cont < (numSens - 1))
      Serial.print(", ");
    else
      Serial.print("\n");
  }
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




