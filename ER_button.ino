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
      if (Serial.available() > 0) {
        int input = Serial.read();
        lcd.clear();
        lcd.print("LOADING...");
        top.write(75);
        delay(500);

        switch (input) {
          case '1':
            top.write(30);
            delay(2000);
            Serial.println("red");
            top.write(0);
            bottom.write(0);
            delay(700);
            count_red += 1;  // counter
            total += 1;
            //lcd display prints data
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Colour Identify:");
            lcd.setCursor(0, 1);
            lcd.print("RED");
            top.write(75);
            delay(500);
            break;

          case '2':
            top.write(30);
            delay(2000);
            Serial.println("orange");
            top.write(0);
            bottom.write(50);
            delay(500);
            count_orange += 1; //counter
            total += 1;
            // servo motor send candy to container

            //lcd display prints data
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Colour Identify:");
            lcd.setCursor(0, 1);
            lcd.print("ORANGE");
            top.write(75);
            delay(500);
            break;

          case '3':
            top.write(30);
            delay(2000);
            Serial.println("yellow");
            top.write(0);
            bottom.write(50);
            delay(500);
            count_yellow += 1;  //counter
            total += 1;
            // servo motor send candy to container
            //lcd display prints data
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Colour Identify:");
            lcd.setCursor(0, 1);
            lcd.print("YELLOW");
            top.write(75);
            delay(500);
            break;

          case '4':
            top.write(30);
            delay(2000);
            Serial.println("green");
            top.write(0);
            bottom.write(100);
            delay(500);
            count_green += 1;  //counter
            total += 1;
            // servo motor send candy to container
            //lcd display prints data
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Colour Identify:");
            lcd.setCursor(0, 1);
            lcd.print("GREEN");
            top.write(75);
            delay(500);
            break;

          case '0':
            top.write(30);
            delay(2000);
            Serial.println("OUT OF RANGE");
            top.write(0);
            delay(700);
            bottom.write(140);
            delay(500);
            count_other += 1;  //counter
            total += 1;
            //lcd display prints data
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Colour Identify:");
            lcd.setCursor(0, 1);
            lcd.print("OUT OF RANGE");
            top.write(75);
            delay(500);
            break;
        }
        delay(1000);
      }
    }
    else {
      start = false;
    }
  }
}

void e_stop_ISR(void) {
  detachInterrupt(digitalPinToInterrupt(ES));
  e_stop = !e_stop;
  state = digitalRead(ES);
  digitalWrite(signallight, state);
  lcd.clear();
  lcd.noAutoscroll();
  lcd.print("EMERGENCY STOP!");
  digitalWrite(signallight, HIGH);
  tone(buzz, 1000, 3000);
  lcd.clear();
  lcd.print("done sorting");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:" + String(count_red) + " O:" + String(count_orange) + " G:" + String(count_green) + " Y:" + String(count_yellow) + " BR:" + String(count_brown) + " BL:" + String(count_blue) + " ER:" + String(count_other));
  lcd.setCursor(0, 1);
  lcd.print("Total: " + String(total));
  for (int i = 0 ; i < 16; i++) {
    lcd.scrollDisplayLeft();// scroll to the left for the string
    delay(700);
  }
  start = false;
}
