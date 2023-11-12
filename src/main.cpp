#include <Arduino.h>
#include <ESP8266WiFi.h>

const int trigPin = D2;  
const int echoPin = D1;  
const int motorPin = D5;
const int countTransPin =D6;
const int countLedPin =D7;
const float HALFSOUNDSPEED=0.034/2;
const long SP_TIMER_MOTOR=800; //1s (ms)
const long SP_TIMER_WAIT=500000; //0.5s (us)
const long SP_TIMER_DEBUG=1000; 
const int SP_BRIZG=1;
const int SP_DISTANCE=35;

// defines variables

int distance;
long timer_start_wait;
long timer_start_motor;
long timer_start_debug;
long timer_current;
int counter_brizg;
int counter_pre_state;

enum state{
  WAIT,
  WORK,
  BLOCK
};
enum state current_state;

long GetDistance(){
  long duration;
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  return duration*0.034/2;
}

void ShotWater(long sp_delay)
  {
    digitalWrite(motorPin, HIGH);
    delay (sp_delay);
    digitalWrite(motorPin, LOW);
  }

void setup() {
  // WiFi.setSleepMode(WIFI_MODEM_SLEEP);
  // WiFi.forceSleepBegin(); delay(1);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(motorPin, OUTPUT); // Sets the trigPin as an Output
// pinMode(countLedPin, OUTPUT); // Sets the trigPin as an Output
// pinMode(countTransPin, INPUT); // Sets the echoPin as an Input
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
// Serial.begin(9600); // Starts the serial communication
// distance=SP_DISTANCE+10;
// digitalWrite(trigPin, LOW);
// digitalWrite(countLedPin, HIGH);
// counter_brizg=0;
// current_state=WAIT;
// timer_start_wait=millis();
// timer_start_debug=timer_start_wait;
if (GetDistance()<SP_DISTANCE) ShotWater(SP_TIMER_MOTOR);
ESP.deepSleep(5e6); 
}



// void GetValBrizg(){
//   int read;
//   read=digitalRead(countTransPin);
//   delayMicroseconds(5000);
//   if (1==read && 1==counter_pre_state) return;
//   if (0==read && 0==counter_pre_state) return;
//   if (0==read && 1==counter_pre_state) {
//     timer_start_motor=millis();
//     counter_brizg=counter_brizg+1;
//     Serial.println(counter_brizg);
//     counter_pre_state=0;
//     return;
//   } 
//   if (1==read && 0==counter_pre_state){
//     counter_pre_state=1;
//   }
// }

// void PrintDebug(){
//   if (millis()-timer_start_debug> SP_TIMER_DEBUG){
//     timer_start_debug=millis();
//     // Prints the distance on the Serial Monitor
//     Serial.print("Distance: ");
//     Serial.println(distance);
//     Serial.print("State: ");
//     Serial.println(current_state);
//     Serial.print("current_trans: ");
//     Serial.print(digitalRead(countTransPin));
//     Serial.print(" pre_trans: ");
//     Serial.print(counter_pre_state);
//     Serial.print(" counter: ");
//     Serial.println(counter_brizg);
//     // Serial.print(" time motor: ");
//     // Serial.print(millis()-timer_start_motor);
//     // Serial.print(" timer_start_motor: ");
//     // Serial.println(timer_start_motor);
//   }
// }

void loop() {}



// void loop() {
//   PrintDebug();
//   switch (current_state){
//     case WAIT:
//       if (millis()-timer_start_wait > SP_TIMER_WAIT) GetDistance();
//       // ESP.deepSleep(SP_TIMER_WAIT);
//       // GetDistance();

//       if (SP_DISTANCE > distance){
//         digitalWrite(motorPin, HIGH); ///!
//         timer_start_motor=millis();
//         current_state=WORK;
//       }
//       break;
//     case WORK:
//       GetValBrizg();
//       if (SP_BRIZG==counter_brizg)
//       {
//         counter_brizg=0;
//         digitalWrite(motorPin, LOW);
//         current_state=WAIT;
//         GetDistance();
//         timer_start_wait=millis();

//       }
//       if (millis()-timer_start_motor>SP_TIMER_MOTOR) 
//       {
//         digitalWrite(motorPin, LOW);
//         counter_brizg=0;
//         current_state=BLOCK;
//       }
//       break;
//     case BLOCK:

//     default:
//       break;
//   }
// }

