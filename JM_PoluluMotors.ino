//Code written by Juan F Martinez
//Shared to and Modified for Medical Robotics Club at GT
//Editor: Hyungjun Park{RICHY} on 10/09/2022

#include <BasicLinearAlgebra.h>
using namespace BLA;
#include <ElementStorage.h>

#define ENCA1 5
#define ENCB1 7
#define ENCA2 14
#define ENCB2 16 
#define ENCA3 18
#define ENCB3 20 
#define PWM1 2
#define PHASE1 52
#define PWM2 3
#define PHASE2 50
#define PWM3 4
#define PHASE3 48

int pos1 = 0; int pos2 = 0; int pos3 = 0;
long prevT = 0;
float errorPrevious1 = 0; float errorPrevious2 = 0; float errorPrevious3 = 0;
float errorIntegral1 = 0; float errorIntegral2 = 0; float errorIntegral3 = 0;
int x = 0; int y = 0; int z = 0;
int targetPos1 = 0; int targetPos2 = 0; int targetPos3 = 0;
int L1 = 10; int L2 = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  pinMode(ENCA3, INPUT);
  pinMode(ENCB3, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA1),readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2),readEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA3),readEncoder3, RISING);
}

void loop() {
//  
  targetPos1 = 200*sin(2*(prevT/1e6));
  targetPos2 = 400*sin(3*(prevT/1e6));
  targetPos3 = 300*sin(2*(prevT/1e6));

  float kp1 = 2; float kp2 = 2; float kp3 = 2;
  float ki1 = 0; float ki2 = 0; float ki3 = 0;
  float kd1 = 0; float kd2 = 0; float kd3 = 0;


//FIRST MOTOR      //////////////
  long currentTime = micros();
  float deltaT = float((currentTime - prevT)/1e6);
  prevT = currentTime;
  
  int e1 = targetPos1-pos1;
  float derivativeE1 = (e1 - errorPrevious1)/(deltaT);
  errorIntegral1 = errorIntegral1 + e1*deltaT;
  
  float motorInput1 = (kp1 * e1) + (kd1 * derivativeE1) + (ki1 * errorIntegral1);
  
// set motor power based on the control signal
  float pwr1 = fabs(motorInput1);
  if (pwr1 > 255) {
    pwr1 = 255;
  }
// set the motor direction based on the control signal
  int dir1 = 1;
  if (motorInput1<0){
    dir1 = -1;
  }
//now send the command to the motor
  setMotor1(dir1,pwr1,PWM1,PHASE1);

// SECOND MOTOR     ///////////
  
  int e2 = targetPos2-pos2;
  float derivativeE2 = (e2 - errorPrevious2)/(deltaT);
  errorIntegral2 = errorIntegral2 + e2*deltaT;
  
  float motorInput2 = (kp2 * e2) + (kd2 * derivativeE2) + (ki2 * errorIntegral2);
  
// set motor power based on the control signal
  float pwr2 = fabs(motorInput2);
  if (pwr2 > 255) {
    pwr2 = 255;
  }
// set the motor direction based on the control signal
  int dir2 = 1;
  if (motorInput2<0){
    dir2 = -1;
  }
  setMotor2(dir2,pwr2,PWM2,PHASE2);

//THIRD MOTOR   ////////////
  
  int e3 = targetPos3-pos3;
  float derivativeE3 = (e3 - errorPrevious3)/(deltaT);
  errorIntegral3 = errorIntegral3 + e3*deltaT;
  
  float motorInput3 = (kp3 * e3) + (kd3 * derivativeE3) + (ki3 * errorIntegral3);
  
// set motor power based on the control signal
  float pwr3 = fabs(motorInput3);
  if (pwr3 > 255) {
    pwr3 = 255;
  }
// set the motor direction based on the control signal
  int dir3 = 1;
  if (motorInput3<0){
    dir3 = -1;
  }
  setMotor3(dir3,pwr3,PWM3,PHASE3);

// save error data
  errorPrevious1 = e1;
  errorPrevious2 = e2;
  errorPrevious3 = e3;

  Serial.print(targetPos1);
  Serial.print(" ");
  Serial.print(pos1);
  Serial.print(" ");
  Serial.print(targetPos2);
  Serial.print(" ");
  Serial.print(pos2);
  Serial.print(" ");
  Serial.print(targetPos3);
  Serial.print(" ");
  Serial.print(pos3);
  Serial.println();
}


void setMotor1(int dir1, int pwmVal1, int pwm1, int phase1){
  analogWrite(pwm1,pwmVal1);
  if (dir1 == 1) {
    digitalWrite(phase1, HIGH);
  }
  else if (dir1 == -1){
    digitalWrite(phase1, LOW);
  }
}
void setMotor2(int dir2, int pwmVal2, int pwm2, int phase2){
  analogWrite(pwm2,pwmVal2);
  if (dir2 == 1) {
    digitalWrite(phase2, HIGH);
  }
  else if (dir2 == -1){
    digitalWrite(phase2, LOW);
  }
}
void setMotor3(int dir3, int pwmVal3, int pwm3, int phase3){
  analogWrite(pwm3,pwmVal3);
  if (dir3 == 1) {
    digitalWrite(phase3, HIGH);
  }
  else if (dir3 == -1){
    digitalWrite(phase3, LOW);
  }
}

int calculateTarget( int x, int y, int z, int L1, int L2 ) {
  BLA:: Matrix <3,1> A = {x,y,z};
  // take in data as an x,y,z coordinate and translate that into motor angles
  // use inverse kinematics calculated
  float theta1 = atan(z/x);
  BLA:: Matrix <3,3> Roto1 = {cos(theta1), 0, sin(theta1), 
                                  0      , 1,      0,
                             -sin(theta1), 0, cos(theta1)};
  theta1 = theta1 * 57296 / 1000;

  BLA:: Matrix <3> C = Roto1 * A;

  x = C(1);
  y = C(2);
  
  float theta3 = acos((x*x + y*y - L1*L1 - L2*L2) / (2*L1 *L2)) ;
  float theta2 = atan(y/x) + atan((L2 * sin(theta3)) / ( L1 + L2 * cos(theta3)));
}

void readEncoder1() {

  int b = digitalRead(ENCB1);
  if (b>0) {
    pos1 ++;
  }
  else {
    pos1--;
  }
}
void readEncoder2() {

  int c = digitalRead(ENCB2);
  if (c>0) {
    pos2 ++;
  }
  else {
    pos2--;
  }
}

void readEncoder3() {

  int d = digitalRead(ENCB3);
  if (d>0) {
    pos3 ++;
  }
  else {
    pos3--;
  }
}
