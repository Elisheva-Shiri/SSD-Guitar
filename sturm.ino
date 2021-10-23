// include the Servo library
#include <Servo.h>

const int COMMON = 2;

struct StateButton
{
  bool state;
  int a;
  int b;
};

StateButton Buttons[3];

const int SERVO_NUM = 6 ;
const int STRUM_NUM = 3 ;

unsigned long lastFire = 0;
unsigned long currStrum = 0;

// create a servo objects
Servo myServos[SERVO_NUM] ={};
bool myServosState[SERVO_NUM] ={};  

const int servoPin[SERVO_NUM] = {6,7,8,9,10,11}; // digital pin used to connect the servo
int angles[SERVO_NUM] = {0};   // variable to hold the angle for the servo motor
int angleOpen = 85;
int angleClose = 115;

void configureCommon() {
 // pinMode(COMMON, INPUT_PULLUP);

 // pinMode(B_PLUS, OUTPUT);
 // digitalWrite(B_PLUS, LOW);

 // pinMode(B_MINUS, OUTPUT);
  //digitalWrite(B_MINUS, LOW);
}

bool getButtonState(StateButton sb)
{
  Serial.print(digitalRead(Buttons[0].a));
  //Serial.println(digitalRead(sb.b));
  return digitalRead(sb.a);
}
void configureDistinct() {
  pinMode(COMMON, OUTPUT);
  digitalWrite(COMMON, LOW);

 // pinMode(B_PLUS, INPUT_PULLUP);
 // pinMode(B_MINUS, INPUT_PULLUP);
}

void pressInterrupt() { // ISR
}

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
  
  Buttons[0].a = 14;
  Buttons[0].b = 15;
  digitalWrite(Buttons[0].a, LOW);
  digitalWrite(Buttons[0].b, LOW);
  pinMode(Buttons[0].a, INPUT);
  pinMode(Buttons[0].a, INPUT);
  Buttons[1].state = getButtonState(Buttons[0]);
  
  Buttons[1].a = 18;
  Buttons[1].b = 19;

  pinMode(Buttons[1].a, INPUT);
  pinMode(Buttons[1].a, INPUT);
  Buttons[1].state = getButtonState(Buttons[1]);
  
  Buttons[2].a = 22;
  Buttons[2].b = 23;
  digitalWrite(Buttons[2].a, LOW);
  digitalWrite(Buttons[2].b, LOW);
  pinMode(Buttons[2].a, INPUT);
  pinMode(Buttons[2].a, INPUT);
  Buttons[1].state = getButtonState(Buttons[2]);
  
  setAngles();
  //configureCommon();
  //attachInterrupt(digitalPinToInterrupt(COMMON), pressInterrupt, FALLING);
  
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].attach(servoPin[i]); // attaches the servo pin to the servo object
  }

  Serial.write("done");
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

void checkState()
{
  if (Buttons[0].state != getButtonState(Buttons[0]))
  {
    
  }

  if (Buttons[1].state != getButtonState(Buttons[1]))
  {
    currStrum++;
    currStrum %= STRUM_NUM;
  }

  if (Buttons[2].state != getButtonState(Buttons[2]))
  {
    if (currStrum == 0)
    {
      currStrum = STRUM_NUM - 1;
    }
    else
    {
      currStrum--;
    }
  }
}

void setAngles (){
  for (int i = 0; i < SERVO_NUM; i++){
    myServosState[i] = true;
    myServos[i].write(angleOpen);     // set the servo position
  }
}

int getAngle(int i) {
  if (myServosState[i])
  {
    myServosState[i] = false;
    return angleClose;
  }
  myServosState[i] = true;
  return angleOpen;
}

int getBase() //will be controlled by a button
{
  return random(3, 6);
}

void playIndex(int i, bool doDelay = true)
{
  checkState();
  myServos[i].write(getAngle(i));// set the servo position
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