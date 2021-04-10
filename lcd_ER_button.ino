#include <Servo.h>  // include Servo Motor Library
#include <LiquidCrystal.h>
/* RS pin -> 14  A0
   enable pin -> 15 A1
   D4-D7 -> 16-19  A2-A5
*/
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

//emergency stop button
int ES = 2;
int buzz = 12; // sound for emergency stop
int signallight = 13;
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
int count_blue = 0;
int count_brown = 0;
int count_other = 0;
int total = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //emergency button
  pinMode(ES, INPUT_PULLUP);
  pinMode(signallight, OUTPUT);
  delay(100);
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
  lcd.setCursor(0, 0);
  lcd.print("START");
  lcd.setCursor(0, 1);
  lcd.print("LOADING...");
  delay(2500);
}

void loop() {
  if (start == true) {
    if (e_stop == false) {
      lcd.clear();
      lcd.print("START SORTING....");
      top.write(75);
      delay(500);
      colour = readColour();
      delay(10);
      //if (Serial.available() > 0) {
      top.write(30);
      delay(2000);
      // int input = Serial.read();
      switch (colour) {
        case '1':
          Serial.println("red");
          top.write(0);
          bottom.write(0);
          delay(500);

          count_red += 1;  // counter
          total += 1;

          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("RED");
          break;

        case '2':
          Serial.println("orange");
          count_orange += 1; //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(25);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("ORANGE");
          break;

        case '3':
          Serial.println("green");
          count_green += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(50);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("GREEN");
          break;

        case '4':
          Serial.println("yellow");
          count_yellow += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(75);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("YELLOW");
          break;

        case '5':
          Serial.println("brown");
          count_brown += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(100);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("BROWN");
          break;

        case '6':
          Serial.println("blue");
          count_blue += 1;  //counter
          total += 1;
          // servo motor send candy to container
          bottom.write(125);
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("BLUE");
          break;

        case '0':
          top.write(0);
          delay(500);
          Serial.println("OUT");
          count_other += 1;  //counter
          total += 1;
          bottom.write(150);
          Serial.println("OUT OF RANGE");
          //lcd display prints data
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Colour Identify:");
          lcd.setCursor(0, 1);
          lcd.print("OUT OF RANGE");
          break;
      }
      delay(1000);
    }
  }
  else {
    start = false;
  }
}



int readColour() {
  colour = 1;
  colour = 3;
  colour = 4;
  colour = 0;
  colour = 2;
  colour = 5;
  return colour;
}
