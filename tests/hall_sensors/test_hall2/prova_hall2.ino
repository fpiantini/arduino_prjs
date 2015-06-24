/*
 Hall Effect Switch - TEST 2
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when one of two Hall Effect Sensor attached to input pins
 is triggered by a magnet. The complete sensors status is written
 to the serial console.
 Changed from test 1: to drive the hall sensors, two digital outputs 
 are used instead of the 5 Vcc pin.
 The driver outputs are set to HIGH only before to read the
 correspondant sensor. 
 
 Hall effect sensor used is the A1120EUA from Allegro Microsystems
 
 This example code is written starting by the following tutorial:
 http://www.hobbytronics.co.uk/arduino-tutorial8-hall-effect
 
 and it is in the public domain:
 http://www.fpiantini.it/
 
*/

#include "halldefs.h"

// **********************************************************
// VARIABLES --------------------------------
HallArrayInfo_t hai;

// **********************************************************

// * * * * * * * * * * * * * * * * * * * * * * * * *
void setup() {
  int cont;
  
  // initialize application data
  InitHallArrayInfo(&hai);

  // initialize serial console and print banner
  Serial.begin(9600); // This sets up a serial connection, 9.6 kbts/s.
  Serial.println("Hall sensor TEST1, by F. Piantini, 20140111");

  // initialize the LED pin as an output and turns it off
  pinMode(hai.led_pin, OUTPUT);
  digitalWrite(hai.led_pin, LOW); 

  // initialize the hall effect sensor pins as inputs
  // and initialize status
  for (cont = 0; cont < hai.num_sens; cont++) {
    pinMode(hai.hall_pins_lines[cont], INPUT);
    hai.hall_state[cont] = -1;
    pinMode(hai.hall_vcc_lines[cont], OUTPUT);
  }

}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void loop() {
  int stat_changed = false;
  
  // update the state of the hall effect sensors
  stat_changed = ReadAllSensor();

  if (stat_changed == true) {
    updateLed(hai.one_active);
    printStatus();
  }
}


// * * * * * * * * * * * * * * * * * * * * * * * * *
void InitHallArrayInfo(HallArrayInfo_t* p_hai)
{
  int cont;
  
  p_hai->led_pin = 13;
  p_hai->num_sens = 2;
  p_hai->hall_vcc_lines[0] = 2;
  p_hai->hall_vcc_lines[1] = 3;
  p_hai->hall_pins_lines[0] = 7;
  p_hai->hall_pins_lines[1] = 8;
  p_hai->one_active = false;

  for (cont = 0; cont < NUM_SENSORS_MAX; cont++)
    p_hai->hall_state[cont] = -1;

}


// * * * * * * * * * * * * * * * * * * * * * * * * *
int  ReadAllSensor() {
  int new_state = LOW;
  int changed = false;
  int cont;

  hai.one_active = false;
  for (cont = 0; cont < hai.num_sens; cont++) {
    
    new_state = ReadSensor(hai.hall_vcc_lines[cont], 
                     hai.hall_pins_lines[cont]);
    if (new_state != hai.hall_state[cont]) {
      hai.hall_state[cont] = new_state;
      changed = true;
    }

    if (hai.hall_state[cont] == LOW)
      hai.one_active = true;
  }

  return changed;
}

// * * * * * * * * * * * * * * * * * * * * * * * * *
int  ReadSensor(int vcc_line, int sensor_line) {
  int state = LOW;
  
  digitalWrite(vcc_line, HIGH);
  // the following delay is necessary to allow the Vcc line
  // to stabilize before to perform the read of the sensor
  // status
  delay(1);
  state = digitalRead(sensor_line);  
  digitalWrite(vcc_line, LOW);
  delay(1);

  return state;
}

// * * * * * * * * * * * * * * * * * * * * * * * * *
void printStatus() {
  int cont;
  
  Serial.print("Hall sensor status changed:  ");
  for (cont = 0; cont < hai.num_sens; cont++) {
    Serial.print(hai.hall_state[cont]);
    if (cont < (hai.num_sens - 1))
      Serial.print(", ");
    else
      Serial.print("\n");
  }
}

  
// * * * * * * * * * * * * * * * * * * * * * * * * *
void updateLed(int oneActive) {  
  if (oneActive == true) {     
    // turn LED on:    
    digitalWrite(hai.led_pin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(hai.led_pin, LOW); 
  }
}




