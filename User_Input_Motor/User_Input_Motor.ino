//Code written by Juan F Martinez
//Shared to and Modified for Medical Robotics Club at GT
//Editor: Hyungjun Park{RICHY} and Natasha Setiadi on 10/09/2022
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PWM1 2
#define PWM2 3
#define PWM3 4
#define PHASE1 52
#define PHASE2 50
#define PHASE3 48
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     9

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  8

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)

char userInput;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  userInput = Serial.read();

//now send the command to the motor
if(userInput == 'u'){
analogWrite(PWM1, 255);
digitalWrite(PHASE1, HIGH);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, HIGH);
}

  if(userInput == 's'){
analogWrite(PWM1, 0);
analogWrite(PWM2, 0);
analogWrite(PWM3, 0);
  }
if(userInput == 'd'){
analogWrite(PWM1, 255);
digitalWrite(PHASE1, LOW);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, LOW);

  }

if(userInput == 'r'){
analogWrite(PWM1, 255);
digitalWrite(PHASE1, HIGH);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, LOW);

}
if(userInput == 'l'){
analogWrite(PWM1, 255);
digitalWrite(PHASE1, LOW);
analogWrite(PWM2, 255);
digitalWrite(PHASE2, HIGH);

}
if(userInput == 'c'){
analogWrite(PWM3, 255);
digitalWrite(PHASE3, HIGH);
}
if(userInput == 'x'){
analogWrite(PWM3, 255);
digitalWrite(PHASE3, LOW);
}
for(int i=0;i<LED_COUNT;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,100,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}

