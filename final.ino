/* Author: Kelly Mak
   Date: January 26, 2021
   TEJ4M1 - Mr Cho
    Colour Sorter Project: using the colour sensor and servo motors to sort the skittles into
                           different containers based on their colours
*/

// add in libraries for servo motors and lcd display
#include <Servo.h>
#include <LiquidCrystal.h>
/* RS pin -> 14  A0
   enable pin -> 15 A1
   D4-D7 -> 16-19  A2-A5
*/
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);  // define pins

//emergency stop button
int ES = 2;
int buzz = 12; // sound for emergency stop
int signallight = 13;  // light for emergency stop
//global variables
boolean start = true;
volatile boolean e_stop = false;
volatile int state = 0;

// define colour sensor
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut A7

// define servo motors (top and bottom)
Servo top;
Servo bottom;

// variables for counters and frequency
int freq = 0;
int colour = 0;
int count_red = 0;
int count_orange = 0;
int count_green = 0;
int count_yellow = 0;
int count_other = 0;
int total = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //emergency button
  pinMode(ES, INPUT_PULLUP);  // set emergency button as input
  pinMode(signallight, OUTPUT);
  delay(100);
  attachInterrupt(digitalPinToInterrupt(ES), e_stop_ISR, CHANGE);  // change state
  //colour sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, OUTPUT);

  //set frequency scale to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  //servo motors
  top.attach(9); // connect to arduino D9
  bottom.attach(10); // connect to arduino D10

  //lcd display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  // start at coloumn 0 and line 0
  lcd.print("START");
  lcd.setCursor(0, 1);  // start at column 0 and line 1
  lcd.print("LOADING...");
  delay(2500);  // stay for 2.5s
}

void loop() {
  if (start == true) {
    if (e_stop == false) { // if emergency button is not pressed
      lcd.clear();
      lcd.print("START SORTING....");
      bottom.write(0);
      top.write(75);
      delay(500);
      for (int i = 75; i > 20; i--) { // get candy
        top.write(i);
        delay(2);
      }
      delay(500);

      colour = readColour();  // get result from readcolour
      delay(10);

      switch (colour) { //sort to the corresponding container for each colour
        case 1:
          count_red += 1;  // counter
          total += 1;
          // servo moter send candy to container
          bottom.write(0);
          delay(700);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("RED");
          break;

        case 2:
          count_orange += 1; //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(50);
          delay(700);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("ORANGE");
          break;

        case 3:
          count_yellow += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(50);
          delay(700);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("YELLOW");
          break;

        case 4:
          count_green += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(100);
          delay(700);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("GREEN");
          break;

        case 0:
          count_other += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(140);
          delay(700);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("OUT OF RANGE");
          break;

        case 9:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("R:" + String(count_red) + " O:" + String(count_orange) + " G:" + String(count_green) + " Y:" + String(count_yellow) + " OUT:" + String(count_other));
          lcd.setCursor(0, 1);
          lcd.print("Total: " + String(total));
          for (int i = 0 ; i < 16; i++) {
            lcd.scrollDisplayLeft();// scroll to the left for the string
            delay(700);
          }
      }
      delay(1000);
      // after sorting a certain amount of skittles, it will print of the numbers of colours

      for (int i = 20; i > 0; i--) {  // servo motor send to bottom motor
        top.write(i);
        delay(2);
      }
      delay(200);

      for (int i = 0; i < 75; i++) { // send to container and return back to get next candy
        top.write(i);
        delay(2);
      }
      colour = 0;
    }
    else { // as emergency is pressed
      start = false;
    }
  }
}

void e_stop_ISR(void) {  // stop the program
  detachInterrupt(digitalPinToInterrupt(ES));
  e_stop = !e_stop;
  state = digitalRead(ES);
  digitalWrite(signallight, state);
  lcd.clear();
  lcd.noAutoscroll();
  lcd.print("EMERGENCY STOP!");
  digitalWrite(signallight, HIGH);
  tone(buzz, 1000, 3000);
  start = false;
}


//function for reading the colours
int readColour() {
  // set red photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  //read output frequency
  freq = pulseIn(sensorOut, LOW);
  int R = freq;
  //print value
  Serial.print("R= ");  //name
  Serial.print(freq);  // red colour
  Serial.println("  ");
  delay(50);

  // set green photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  //read output frequency
  freq = pulseIn(sensorOut, LOW);
  int G = freq;
  //print value
  Serial.print("G= ");  // name
  Serial.print(freq);  // colour
  Serial.println("  ");
  delay(50);

  // set blue photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  //read output frequency
  freq = pulseIn(sensorOut, LOW);
  int B = freq;
  //print value
  Serial.print("B= ");  // name
  Serial.print(freq);  // colour
  Serial.println("  ");
  delay(50);

  // detect colours and return the colur value for sorting
  if (R < 32 & R > 29 & G < 40 & G > 36 & B < 33 & B > 29) {  // colour range
    colour = 1; // red
  }
  else if (R < 28 & R > 25 & G < 37 & G > 34 & B < 31 & B > 28) {// colour range
    colour = 2;  //orange
  }
  else if (R < 27 & R > 24 & G < 32 & G > 29 & B < 30 & B > 27) {// colour range
    colour = 3;  //yellow
  }
  else if (R < 38 & R > 35 & G < 41 & G > 39 & B < 36 & B > 34) {// colour range
    colour = 4;  //green
  }
  else if (R < 35 & R > 32 & G < 36 & G > 32 & B < 29 & B > 26) {
    colour = 9;  // when the colur sensor detect nothing (the cardboard)
  }
  else {
    colour = 0; // out of range colour
  }
  return colour;
}
