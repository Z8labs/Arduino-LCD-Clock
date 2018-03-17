/*The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>
#include <stdio.h>

int s = 0;  //change this value to change the starting seccond
int m = 0;  //change this value to change the starting miniut
int h = 0;  //change this value to change the starting hour
int AP = 1; //controlls the state between AM and PM. 1 = AM, 2 = PM

unsigned long curMillis, preMillis, elapMillis;
char timeOut[16];

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2); 
  lcd.setCursor(12, 1); 
  if(AP == 1){
    lcd.print("AM");
  }
  else{
    AP = 2;
    lcd.print("PM");
  }
}

void loop(){
  timeSet();
  sprintf(timeOut, "%02d:%02d:%02d", h, m, s);
  lcd.setCursor(3, 1);
  lcd.print(timeOut);
}

void timeSet(){
  curMillis = millis();
  elapMillis += curMillis - preMillis;

  if(elapMillis >= 1000){
    s++;
    elapMillis = elapMillis - 1000;
  }

  preMillis = curMillis;
  
  if(s >= 60){
    s = 0;
    m++;
  }
  if(m >= 60){
    m = 0;
    h++;
  }
  if(h >= 13){
    h = 1;
  }

  if(h >= 12){
    if(m == 0){
      if(s == 1){
        if(AP == 1){
          AP = 2;
          lcd.setCursor(12, 1);
          lcd.print("AM");
          delay(750);
        }
        else{
          AP = 1;
          lcd.setCursor(12, 1);
          lcd.print("PM");
          delay(750);
        }
      }
    }
  }
}

