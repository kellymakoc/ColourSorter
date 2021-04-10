#include <LiquidCrystal.h>
LiquidCrystal lcd(14,15,16,17,18,19);
int pin = 2;
int light = 13;

int buzz = 12;

boolean start = true;
volatile boolean e_stop = false;
volatile int state = 0;
int count_red = 0;
int count_orange = 0;
int count_green = 0;
int count_yellow = 0;
int count_blue = 0;
int count_brown = 0;
int count_other = 0;
int total = 0;

void setup(){
  pinMode(pin, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  Serial.begin(9600);
  delay(100);
  attachInterrupt(digitalPinToInterrupt(pin), e_stop_ISR, CHANGE);

  //lcd display
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("START");
  lcd.setCursor(0,1);
  lcd.print("loading...");
  delay(2500);
}

void loop(){
  if(start == true){
    if (e_stop == false){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("R:"+ String(count_red)+ " O:" + String(count_orange) + " G:"+ String(count_green)+ " Y:" + String(count_yellow) + " BR:"+ String(count_brown)+ " BL:" + String(count_blue) +" ER:"+ String(count_other));
      lcd.setCursor(0,1);
      lcd.print("Total: " + String(total));
      for (int i = 0 ; i < 16; i++){
        lcd.scrollDisplayLeft();
        delay(700);
       }
      delay(3000);
  }
  else{
    start = false;
  }
}
}

void e_stop_ISR(void){
  detachInterrupt(digitalPinToInterrupt(pin));
  e_stop = !e_stop;
  state = digitalRead(pin);
  digitalWrite(light, state);
  lcd.clear();
  //lcd.setCursor(0,0);
  lcd.noAutoscroll();
  lcd.print("EMERGENCY STOP");
  digitalWrite(light, HIGH);
  tone(buzz, 1000, 3000);
  start = false;
}
