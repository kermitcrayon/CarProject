#include "LineFollow.h"
#include "MotorDrive.h"

  #define sensor1 10  // New sensor connected to digital pin 10
  #define sensor4 11  // New sensor connected to digital pin 11  
  #define slavetimer 200 // timer for the delay

void SlaveMode() {
  unsigned long startcount = millis(); // Start's the millis count   
  int val1 = 0; // Initialize val1 for sensor1
  int val2 = 0; // Initialize val2 for sensor4
  int timerleft;
  int timerright;

  unsigned long endcount = 0;  
  pinMode(sensor1, INPUT);    // Set sensor1 as INPUT
  pinMode(sensor4, INPUT);   // Set sensor1 as INPUT  
  val1 = digitalRead(sensor1); // Read sensor1
  val2 = digitalRead(sensor4); // Read sensor4

  if (val1 == HIGH && val2 == HIGH) {  // Check if either of the sensors detects the line (HIGH)
    forward();
  } else {// If both sensors are HIGH, the car is on the line

    if (val1 == LOW && val2 == HIGH) {  // Check if sensor1 detects the line
        timerleft = 1;      
    } else{
      if(startcount - endcount >= slavetimer){
       timerleft = 0;
      }
    }
    if (val1 == HIGH && val2 == LOW) {  // Check if sensor4 detects the line  
      timerright = 1;  
    } else{
      if(startcount - endcount >= slavetimer){
       timerright = 0;
      }
    }
    if (val1 == LOW && val2 == LOW) {  // Check if sensor4 detects the line  
      forward(); // Turn left 
    }
  } 
  endcount = startcount;
  if(timerleft = 1){
    tankleft();  
  }
  if(timerright = 1){
    tankright();  
  }  
}
