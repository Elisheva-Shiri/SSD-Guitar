// include the Servo library
#include <Servo.h>

const int SERVO_NUM = 6 ; 

// create a servo objects
Servo myServos[SERVO_NUM] ={};  


const int servoPin[SERVO_NUM] = {4,5,6,7,8,9}; // digital pin used to connect the servo
int angles[SERVO_NUM] = {0};   // variable to hold the angle for the servo motor
int angleOpen = 70; //middle 85
int angleClose = 100 ;

static bool flag = true;
int angle = 0;

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].attach(servoPin[i]); // attaches the servo pin to the servo object
  }
}

void loop() {
  firstStrum();
  secondStrum();
  thirdStrum();
  delay(1000);     // wait for the servo to get there
}

void firstStrum (){
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleOpen);     // set the servo position
    delay(300);
  }
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleClose);     // set the servo position
    delay(300);
  }
}

void secondStrum (){
  if (flag)
    angle = angleOpen;
  else
    angle = angleClose;
    
  myServos[0].write(angle);
  myServos[5].write(angle);
  delay(300);
  myServos[1].write(angle);
  myServos[4].write(angle);
  delay(300);
  myServos[2].write(angle);
  myServos[3].write(angle);
  
  flag = !flag;
}

void thirdStrum (){
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleOpen);     // set the servo position
    delay(300);
    i += 2;
  }

 for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleOpen);     // set the servo position
    delay(300);
    i += 2;
  }
  for (int i = 0; i < SERVO_NUM; i++){
    myServos[i].write(angleClose);     // set the servo position
    delay(300);
  }
}
