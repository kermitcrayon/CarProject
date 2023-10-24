#include "F567.h"

unsigned long previousMillis1 = 0;  
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long previousTime = 0;
unsigned long interval = 1000;

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
    // delay(100);
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
    lcd.print(speed(value));
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