#include <SindormirSevenSegments.h>

SindormirSevenSegments  cpuDisplay;
SindormirSevenSegments  playerDisplay;

int potPin = 5;
int potValue = 0; 

int playerDisplayNumber = 0;
int cpuDisplayNumber = 0;

int points = 0;
int missCounter = 0;

long previousMillis = 0; 
long interval = 3000;
bool resetTimer = false;

void setup() {
   cpuDisplay.commonType(CATODO);
   cpuDisplay.attach(3,2,7,8,9,4,5,6);
   playerDisplay.commonType(CATODO);
   playerDisplay.attach(15, 14, 19, 20, 21, 16, 17, 18);
   start();
   cpuPlay();   
}

void Blink(SindormirSevenSegments ssdisplay, int times, int delayMilliseconds)
{
  ssdisplay.clear();
  delay(delayMilliseconds);
  for (int i = 0; i < times; i++)
  {
      ssdisplay.lampTest();
      delay(delayMilliseconds);
      ssdisplay.clear();
      delay(delayMilliseconds);
  }
}

void loop() {
   potValue = analogRead(potPin);
   playerDisplayNumber = ConvertToDigit(potValue);
   playerDisplay.print(playerDisplayNumber);
      
   if (playerDisplayNumber == cpuDisplayNumber)
   {
      points++;
      Blink(cpuDisplay, 5, 150);
      cpuPlay();   
      resetTimer = true;
      interval = interval - 100;
   }
   else {
    unsigned long currentMillis = millis();
   
    if(currentMillis - previousMillis > interval) {
      if (resetTimer) {
        resetTimer = false;
      }
      else {
        checkMiss();
      }
      previousMillis = currentMillis;     
    }    
   }
}


void start(){
  Blink(cpuDisplay, 2, 150);
  Blink(playerDisplay, 2, 150);
}


void cpuPlay() {
  cpuDisplayNumber = GenerateRamdomNumber();  
  cpuDisplay.clear();
  delay(150);
  cpuDisplay.print(cpuDisplayNumber);
}

int ConvertToDigit(int value)
{
  return value * 9 / 1000; 
}
 
 
void checkMiss()
{
    if (missCounter < 3) {
      cpuPlay();
      missCounter++;
    }
    else {
       GameOver();
    } 
}
 

int GenerateRamdomNumber() {
  return random(0, 9);
}
 
void GameOver() {
  ShowPoints();
  interval = 3000;
  start();
  points = 0;
  missCounter = 0;
  resetTimer = true;
  cpuPlay();
}

void ShowPoints() {
   float fpoints = points;
   cpuDisplay.print((fpoints / 10)); 
   playerDisplay.print(fmod(fpoints, 10));   
   delay(5000);
}

 

