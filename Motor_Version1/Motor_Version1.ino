#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <NewPing.h>
#include "MotorDrive.h"
#include "LineFollow.h"

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 4, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. //sonar[0]=sensor right side
  NewPing(7, 8, MAX_DISTANCE)  //sonar[1] = sensor left side
};

LiquidCrystal_I2C lcd(0x27,16,2); 

const int buttonReset = 13;
const int buttonSwitch = A0;   
const int buttonMenu = A1;
const int ledLeft = A2;
const int ledRight = A3;

int buttonState,lastButtonState; 
int selectedOption = 1; 
int selectedMenu = 1;
int directionMovement;
int speedmotors = 0;
int forthspeed = 0;
int stick = A0;
int mode = 99;
int add = 0;
int reading;
int timer = 5000;
int seconds, minutes, hours;
int timerleft;
int timerright;
char value;
int speedValue;

const int slavetimer = 200; // timer for the delay
unsigned long endcount = 0;

unsigned long previousMillis1 = 0;  
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousTime = 0;
unsigned long interval = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(stick, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  lcd.backlight();
  digitalWrite(7, LOW);
  pinMode(buttonSwitch, INPUT_PULLUP);
  pinMode(buttonMenu, INPUT_PULLUP);
  seconds = EEPROM.read(0);
  minutes = EEPROM.read(1);
  hours = EEPROM.read(2);  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Reading();
  selectedOption = 3;
	switch(selectedOption){
    case 1: // Auto mode
      speed(7); // set the speed at the predertermint speed    
      AutoMode();
      break;
    case 2: // Remote contro
      RemoteMode();
      break;
    case 3: //  slave mode
      speed(7); // set the speed at the predertermint speed    
      SlaveMode();
      break;
    default: // Await input
      DefaultMode();
      break;
  } 
}
//detect function for uatra sonic sensor
int detectDistance(){            //retrun detection in int, whitch 1=go straight, 2=turn right, 3=turn left, 4=go backward.
  int distance[SONAR_NUM]={0};   //put result in an array.
  int threshold = 50;            //determinde for the minimal distance to react.
  // delay(50);                      //Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  //activate both sensor and store the result in distance[] array.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    distance[i] = sonar[i].ping_cm();
  }

  // if-else statement to determinde whitch derection has obstical.
  if(distance[0]<threshold){    //right detected 
    if(distance[1]<threshold){  //left detects, both have, so go backward.
      return 4;
    }
    else{
      return 2;                 //only right detects, so turn left.
    }
  }
  else{                         //right doesn't detects
    if(distance[1]<threshold){  //only left detects, so turn right.
      return 3;
    }
    else{                       // both don't detect, so go straight.
      return 1;
    }
  }
}

// swicht-case recive case form detectDistance function and call for moving function
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

void RemoteMode() {
	if(Serial.available() > 0){
    value = Serial.read();
    Serial.println(value);
    switch (value){
      case 'f':
        forward();
        Serial.println("FORWARD");
        break;
      case 'r':
        right();
        Serial.println("RIGHT");
        break;
      case 'b':
        backward();
        Serial.println("BACKWARDS");
        break;
      case 'l':
        left();
        Serial.println("LEFT");
        break;
      default:
				speedValue = value.toInt();
        if (speedValue > 0 || speedValue <= 9){
          speed(speedValue);
          Serial.println(speedmotors);
        }
        break;
    }
  }
}

void DefaultMode() {
  Reading();
}

void Reading() {

  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) 
  {
    elapsedTime = elapsedTime + (currentTime - previousTime);
    previousTime = currentTime;
  }
  // delay(100);
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonMenu);
  if (buttonState != lastButtonState)
  {
    if (buttonState == LOW)
    {
      lcd.clear();
      selectedMenu = selectedMenu + 1;
      if (selectedMenu > 3)
      {
        selectedMenu = 1;
      }
    }
  }
  lastButtonState = buttonState;
  switch (selectedMenu){
    case 1: 
    delay(100);
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonSwitch);
    if (buttonState != lastButtonState) 
    {
      if (buttonState == LOW)
      { 
        lcd.clear();
        selectedOption = selectedOption + 1;    
        if( selectedOption > 3)
        {
          selectedOption = 1;
        }
      }
    }
    lastButtonState = buttonState;
    switch (selectedOption) {
      case 1:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("AutoMod");
      break;
      case 2:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("SlaveMod");
      break;
      case 3:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("RadMod");
      break;
      default:
      lcd.setCursor(0, 0);
      lcd.print("Select an option:");
      lcd.setCursor(0, 1);
      lcd.print("sww");
      break;
    }
    break;
    case 2:
    lcd.setCursor(0, 0);
    switch (directionMovement)
    {
      case 1:
      lcd.print("Direction: <");
      break;
      case 2:
      lcd.print("Direction: >");
      break;
      case 3:
      lcd.print("Direction: i");
      break;
      case 4:
      lcd.print("Direction: !");
      break;
      default:
      lcd.print("Direction: -");
      break;
    }
    lcd.setCursor(0, 1);
    lcd.print("Speed:");
    lcd.print(speedmotors);
    break;
    case 3:
    seconds = (seconds + (elapsedTime / 1000)) % 60;
    minutes = (minutes + (elapsedTime / 60000)) % 60;
    hours = (hours + (elapsedTime / 3600000)) % 24;
    lcd.setCursor(4, 0);
    lcd.print(String(hours / 10) + String(hours % 10) + ":" + String(minutes / 10) + String(minutes % 10) + ":" + String(seconds / 10) + String(seconds % 10));
    break;
  }
}

void MakeLed(int make) {
  if(make == 1) {
    digitalWrite(ledLeft, HIGH);
  }
  if(make == 2) {
    digitalWrite(ledRight, HIGH);
  }
}

void speed(int x){
  speedmotors = map(x, 0, 9, 0, 255);
	forthspeed = speedmotors / 4;
}