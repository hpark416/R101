//Code written by Juan F Martinez
//Shared to and Modified for Medical Robotics Club at GT
//Editor: Hyungjun Park{RICHY} and Natasha Setiadi on 10/09/2022

#define PWM1 2
#define PWM2 3
#define PWM3 4
#define PHASE1 52
#define PHASE2 50
#define PHASE3 48
char userInput;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  userInput = Serial.read();

//now send the command to the motor
if(userInput == 'o'){
// setMotor1(dir1,pwr1,PWM1,PHASE1);
analogWrite(PWM1, 255);
digitalWrite(PHASE1, HIGH);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, HIGH);
analogWrite(PWM3, 255);
digitalWrite(PHASE3, HIGH);
}

  if(userInput == 'x'){
analogWrite(PWM1, 0);
analogWrite(PWM2, 0);
analogWrite(PWM3, 0);
  }
if(userInput == 'b'){
analogWrite(PWM1, 255);
digitalWrite(PHASE1, LOW);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, LOW);
analogWrite(PWM3, 255);
digitalWrite(PHASE3, LOW);
  }
}

