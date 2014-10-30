/*
Koass Pad with Octave Control
1/12/14

David Lim and Brandon Wetzel

Move your finger along the X-axis to change the notes
A single octave (C thru A no #'s) is available at a given time

Two buttons are used in increase or decrease the octave

Speaker connected to pin 8

Button 1 is connected to pin 2 - decreases octave
Button 2 is connected to pin 4 - increases octave

*/

#include "pitchesArray.h"

int y1 = A0;
int x2 = A1;
int y2 = A2;
int x1 = A3;

int buttonState1 = 0;
int buttonState2 = 0;
int octaveMultiplier = 3;
boolean pressed=false;


void setup() { 
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
} 


/* Returns X cordinate of touch screen */
int readX(){
  pinMode(y1, INPUT);
  pinMode(x2, OUTPUT);
  pinMode(y2, INPUT);
  pinMode(x1, OUTPUT);

  digitalWrite(x2, LOW);
  digitalWrite(x1, HIGH);

  delay(5); //pause to allow lines to power up

  return analogRead(y1);
}

/* Returns Y cordinate of touch screen */
int readY(){

  pinMode(y1, OUTPUT);
  pinMode(x2, INPUT);
  pinMode(y2, OUTPUT);
  pinMode(x1, INPUT);

  digitalWrite(y1, LOW);
  digitalWrite(y2, HIGH);

  delay(5); // pause to allow lines to power up

  return analogRead(x2);
}

void loop()
{
    int x = readX();
    int y = readY();
    int currNote=NOTE_C4;
    
  
    
    /* To print cordinates 
   if(x < 1000 & y < 1000){
      Serial.print("x: ");
      Serial.print(x-80);
      Serial.print(" - y: ");
      Serial.println(y- 130);  
    } */
  
  
  // Read the state of the pushbutton value:
  buttonState1 = digitalRead(2);
  buttonState2 = digitalRead(4);
  
  // LOW = not pressed HIGH = pressed
  if(buttonState1 == LOW && buttonState2 == LOW)
  {
    pressed=false;
  }
  
  // Octave Down
  if (buttonState1 == HIGH && octaveMultiplier > 0 && !pressed)
    {
      octaveMultiplier = octaveMultiplier - 1;
      Serial.print(octaveMultiplier);
      pressed=true;
    }
  
  // Octave Up
  if(buttonState2 == HIGH && octaveMultiplier < 6 && !pressed)
    {
      octaveMultiplier = octaveMultiplier + 1;
      Serial.print(octaveMultiplier);
      pressed=true;
    }
    
  // X cordinates goes from 0 to 850 (850 % 8 = 106)
  // octaveMultiplier determines starting index in arr[]
  if (x < 1000 && x > 0 && y < 1000)
  {
    if (x<=106)
      tone(8, arr[12*octaveMultiplier+0]);// C
    else if (x>106*1 && x<=106*2)
      tone(8, arr[12*octaveMultiplier+2]);// D
    else if (x>106*2 && x<=106*3)
      tone(8, arr[12*octaveMultiplier+4]);// E
    else if (x>106*3 && x<=106*4)
      tone(8, arr[12*octaveMultiplier+5]);// F
    else if (x>106*4 && x<=106*5)
      tone(8, arr[12*octaveMultiplier+7]);// G
    else if (x>106*5 && x<=106*6)
      tone(8, arr[12*octaveMultiplier+9]);// A
    else if (x>106*6 && x<=106*7)
      tone(8, arr[12*octaveMultiplier+11]);// B
    else if (x>106*7 && x<=106*8)
      tone(8, arr[12*octaveMultiplier+12]);// C  
  }
  else { //turn off sound
    noTone(8);
  }
}
