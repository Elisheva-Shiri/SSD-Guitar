// include the Servo library
#include <Servo.h>

const int COMMON  = 2;
const int B_PLUS  = 10;
const int B_MINUS = 11;

const int SERVO_NUM = 6 ;
const int STRUM_NUM = 3 ;

unsigned long lastFire = 0;
unsigned long currStrum = 0;

// create a servo objects
Servo myServos[SERVO_NUM] ={};  

const int servoPin[SERVO_NUM] = {4,5,6,7,8,9}; // digital pin used to connect the servo
int angles[SERVO_NUM] = {0};   // variable to hold the angle for the servo motor
int angleOpen = 70; //middle 85
int angleClose = 100 ;

void configureCommon() {
  pinMode(COMMON, INPUT_PULLUP);

  pinMode(B_PLUS, OUTPUT);
  digitalWrite(B_PLUS, LOW);

  pinMode(B_MINUS, OUTPUT);
  digitalWrite(B_MINUS, LOW);
}

void configureDistinct() {
  pinMode(COMMON, OUTPUT);
  digitalWrite(COMMON, LOW);

  pinMode(B_PLUS, INPUT_PULLUP);
  pinMode(B_MINUS, INPUT_PULLUP);
}

void pressInterrupt() { // ISR
  if (millis() - lastFire < 200) { // Debounce
    return;
  }
  lastFire = millis();

  configureDistinct(); // Setup pins for testing individual buttons

  if (digitalRead(B_PLUS) == LOW) {
    currStrum++;
    currStrum %= STRUM_NUM;
  } else if (digitalRead(B_MINUS) == LOW){
    if (currStrum == 0)
    {
      currStrum = STRUM_NUM - 1;
    }
    else
    {
      currStrum--;
    }
  }
  Serial.println(currStrum);

  configureCommon(); // Return to original state
}

void setup() {
  Serial.begin(9600); // open a serial connection to your computer

  setAngles();
  configureCommon();
  attachInterrupt(digitalPinToInterrupt(COMMON), pressInterrupt, FALLING);
  
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].attach(servoPin[i]); // attaches the servo pin to the servo object
  }
}

void loop() {
  switch (currStrum)
  {
    case 0:
      firstStrum();
      break;
    case 1:
      secondStrum();
      break;
    case 2:
      thirdStrum();
      break;
    default:
      firstStrum();
  }
}


void setAngles (){
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleOpen);     // set the servo position
  }
}

int getAngle(int angle) {
  if (angle == angleOpen)
  {
    return angleClose;
  }

  return angleOpen;
}

int getBase() //will be controlled by a button
{
  return random(3, 6);
}

void playIndex(int i, bool doDelay = true)
{
  myServos[i].write(getAngle(myServos[i].read()));// set the servo position
  if (doDelay)
    delay(300);
}

void firstStrum(){
  playIndex(getBase());
  playIndex(2);
  playIndex(1);
  playIndex(0);
}

void secondStrum(){
  playIndex(getBase());
  playIndex(2, false);
  playIndex(1, false);
  playIndex(0, false);
  delay(300);
}

void thirdStrum(){
  playIndex(getBase());
  playIndex(2);
  playIndex(1);
  playIndex(0);
  playIndex(1);
  playIndex(2);
  playIndex(0);
  playIndex(1);
}