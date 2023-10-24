#include "MotorDrive.h"

  int speedmotors = 0;
  int forthspeed = 0;

  #define LeftdirPin1 3
  #define LeftdirPin2 5
  #define RightdirPin1 6
  #define RightdirPin2 9

void MotorStart() {
  pinMode(LeftdirPin1, OUTPUT);
  pinMode(LeftdirPin2, OUTPUT);
  pinMode(RightdirPin1, OUTPUT);
  pinMode(RightdirPin2, OUTPUT);
}

int speed(int x){
  speedmotors = map(x, 0, 9, 0, 255);
	forthspeed = speedmotors / 4;
  return speedmotors;
}

void left(){
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, forthspeed);
  digitalWrite(LeftdirPin2, 0); 
}

void right(){ 
  analogWrite(RightdirPin1, forthspeed);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0); 
}

void forward(){
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0);  
}

void backward(){  
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors);  
}

void backLeft() {  
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, forthspeed);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors); 
}

void backRight() {  
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, forthspeed); 
}
void tankleft(){
  analogWrite(RightdirPin1, speedmotors);
  digitalWrite(RightdirPin2, 0);  
  digitalWrite(LeftdirPin1, 0);
  analogWrite(LeftdirPin2, speedmotors); 
}

void tankright(){
  digitalWrite(RightdirPin1, 0);
  analogWrite(RightdirPin2, speedmotors);  
  analogWrite(LeftdirPin1, speedmotors);
  digitalWrite(LeftdirPin2, 0); 
} 