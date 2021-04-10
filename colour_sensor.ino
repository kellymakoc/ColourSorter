#include <Servo.h>
#include <LiquidCrystal.h>
/* RS pin -> 14  A0
   enable pin -> 15 A1
   D4-D7 -> 16-19  A2-A5
*/
// lcd display
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
int count_red = 0;
int count_orange = 0;
int count_green = 0;
int count_yellow = 0;
int count_blue = 0;
int count_brown = 0;
int count_other = 0;
int total = 0;

// servo motors
Servo top;
Servo bottom;

//color sensor
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int freq = 0;
int colour = 0;
void setup() {
  // colour sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // servo motor
  top.attach(9);
  bottom.attach(10);

  Serial.begin(9600);
  //lcd display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("START");
  lcd.setCursor(0, 1);
  lcd.print("LOADING...");
  delay(2500);
}

void loop() {
  lcd.clear();
  lcd.print("START SORTING....");
  top.write(65);
  delay(500);

  //send candy to colour sensor 
  top.write(30);
  delay(1000);
  colour = readColour();
  delay(50);
  switch (colour) {
    case 1:
      Serial.println("red");
      count_red += 1;  // counter
      total += 1;
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
      Serial.println("orange");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Colour Identify:");
      lcd.setCursor(0, 1);
      lcd.print("ORANGE");
      break;

    case 3:
      count_yellow += 1;  //counter
      total += 1;
      Serial.println("yellow");
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
      //lcd display prints data
      Serial.println("green");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Colour Identify:");
      lcd.setCursor(0, 1);
      lcd.print("GREEN");
      break;

    case 5:
      count_blue += 1;  //counter
      total += 1;
      Serial.println("blue");
      //lcd display prints data
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Colour Identify:");
      lcd.setCursor(0, 1);
      lcd.print("BLUE");
      break;

    case 6:
      count_brown += 1;  //counter
      total += 1;
      Serial.println("brown");
      //lcd display prints data
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Colour Identify:");
      lcd.setCursor(0, 1);
      lcd.print("BROWN");
      break;

    case 0:
      count_other += 1;  //counter
      total += 1;
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

int readColour() {
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
  if (R < 85 & R > 79 & G < 115 & G > 111 & B < 90 & B > 88) {
    colour = 1; // red
  }
  else if (R < 28 & R > 25 & G < 37 & G > 34 & B < 31 & B > 28) {
    colour = 2;  //orange
  }
  else if (R < 27 & R > 24 & G < 32 & G > 29 & B < 30 & B > 27) {
    colour = 3;  //yellow
  }
  else if (R < 38 & R > 35 & G < 41 & G > 39 & B < 36 & B > 34) {
    colour = 4;  //green
  }
  else if (R < 37 & R > 34 & G < 37 & G > 33 & B < 29 & B > 26) {
    colour = 5;  //blue
  }
  else if (R < 37 & R > 34 & G < 42 & G > 39 & B < 34 & B > 31) {
    colour = 6;  //brown
  }
  else {
    colour = 0; // out of range colour
  }
  return colour;
}
