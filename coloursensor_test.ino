#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//set frequency 
int freq = 0;
void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, OUTPUT);

  //set frequency scale to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
}

void loop() {
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

}
