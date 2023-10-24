#include "AutoMode.h"

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 2, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. //sonar[0]=sensor right side
  NewPing(4, 4, MAX_DISTANCE),  //sonar[1] = sensor left side
  NewPing(7, 7, MAX_DISTANCE)  //sonar[2] = sensor front side
};

unsigned long previousMilliSensor = 0;

int detectDistance(){            //detect function. retrun detection in int, which 1=go straight, 2=turn left, 3=turn right, 4=go backward.
  int distance[SONAR_NUM]={0};   //put result in an array.
  int threshold = 40;            //determinde for the minimal distance to react.
  //delay(50);                     //Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  unsigned long currentMilliSensor = millis();
  if(currentMilliSensor - previousMilliSensor>50){// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
      previousMilliSensor = currentMilliSensor;
      for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and store the result in distance[] array.
        distance[i] = sonar[i].ping_cm();
    }

    // if-else statement to determinde whitch derection has obstical.
    if((distance[0]<threshold)&&(distance[0]!=0)){    //right detected 
      if((distance[1]<threshold)&&(distance[1]!=0)){  //left detects
          return 4; //both detect, go backwards
        } 
      }
      else{
        return 2;                 //right detects, so turn left.
      }
    }
    else{                         //right doesn't detects
      if((distance[1]<threshold)&&(distance[1]!=0)){  //only left detects, so turn right.
        return 3;
      }
      else{                       // both don't detect, check for sensor in the front
        if((distance[2]<threshold)&&(distance[2]!=0)){ //front detects, go backwards
          return 4; 
        }
        else{
          return 1;
        }
      }
    }
  }
}

void AutoMode(){
  int direction = detectDistance();
  if(direction==4){
    backward();
  }
  else if(direction==2){
    left();
  }
  else if(direction==3){
    right();
  }
  else{
    forward();
  }
}
