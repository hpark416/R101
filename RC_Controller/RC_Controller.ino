// Define Input Connections
#define PWM1 2
#define PWM2 3
#define PWM3 4
#define PHASE1 52
#define PHASE2 50
#define PHASE3 48

#define CH1 8
#define CH2 10
#define CH3 11
#define CH4 12
#define CH5 13
#define CH6 6
 
// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;
 
// Boolean to represent switch value
bool ch6Value;
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}
 
 
void loop() {
  
  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readSwitch(CH6, false);
  
  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.println(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.println(ch2Value);
//forward  
  if(ch2Value > 8){
    analogWrite(PWM3, map(ch2Value,0,100,0,230));
    digitalWrite(PHASE3, HIGH);
    analogWrite(PWM2, map(ch2Value,0,100,0,230));
    digitalWrite(PHASE2, LOW);
  }
//backward
  else if(ch2Value < -8){
    analogWrite(PWM3, map(ch2Value,0,-100,0,230));
    digitalWrite(PHASE3, LOW);
    analogWrite(PWM2, map(ch2Value,0,-100,0,230));
    digitalWrite(PHASE2, HIGH);
  }
  else{
    //if not forward and backward, go left or right
      if(ch1Value > 8){
    analogWrite(PWM3, map(ch1Value,0,100,0,230));
    digitalWrite(PHASE3, LOW);
    analogWrite(PWM2, map(ch1Value,0,100,0,230));
    digitalWrite(PHASE2, LOW);
  }
  else if(ch1Value < -8){
    analogWrite(PWM3, map(ch1Value,0,-100,0,230));
    digitalWrite(PHASE3, HIGH);
    analogWrite(PWM2, map(ch1Value,0,-100,0,230));
    digitalWrite(PHASE2, HIGH);
  }
 else{
    analogWrite(PWM3, 0);
    analogWrite(PWM2, 0);
  }
  }
  Serial.print(" | Ch3: ");
  Serial.println(ch3Value);
  // if(ch3Value > 0){
  //   ch3Value = 0;
  // }
  Serial.print(" | Ch4: ");
  Serial.println(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.println(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);
  
  // delay(500);
}