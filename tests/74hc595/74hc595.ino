//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

// ---------------------------------------------------------
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

// ---------------------------------------------------------
void loop()
{
  cycleOutputs();
  displayAllNumbers();
}

// ---------------------------------------------------------
void displayAllNumbers()
{
  int numberToDisplay;
 
  for (numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    displayNumber(numberToDisplay);
    delay(50);
  }

}

// ---------------------------------------------------------
void cycleOutputs()
{
  int outN;

  for (outN = 1; outN < 9; outN++) {
    enableOutput(outN);
    delay(1000);
  }
  
}

// ---------------------------------------------------------
void enableOutput(int outNum)
{
  int num;
  if ((outNum <= 0) || (outNum > 8))
    return;
  
  num = (1 << (outNum - 1));
  displayNumber(num);
}
  
// ---------------------------------------------------------
void displayNumber(int num)
{
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, num);  

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
}
