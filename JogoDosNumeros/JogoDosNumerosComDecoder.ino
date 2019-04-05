#define PLAYER_DISPLAY 2
#define CPU_DISPLAY 1

#define PLAYER_8 8
#define PLAYER_4 7
#define PLAYER_2 6
#define PLAYER_1 5
#define PLAYER_BLANK 12
#define PLAYER_ALL 13

#define CPU_8 4
#define CPU_4 3
#define CPU_2 2
#define CPU_1 1
#define CPU_BLANK 10
#define CPU_ALL 11

#define POT_PIN 0

int potValue = 0; 

int playerDisplayNumber = 0;
int cpuDisplayNumber = 0;

int points = 0;
int missCounter = 0;


long previousMillis = 0; 
long interval = 3000;
bool resetTimer = false;

void setup() { 
  setOutputPins();
  start();
  cpuPlay();       
}

void loop() {
   potValue = analogRead(POT_PIN);
   playerDisplayNumber = ConvertToDigit(potValue);
   WriteDigit(playerDisplayNumber, PLAYER_DISPLAY);   
   if (playerDisplayNumber == cpuDisplayNumber)
   {
      points++;
      blinkDisplay(CPU_DISPLAY);
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

void setOutputPins()
{
  pinMode(PLAYER_8, OUTPUT);
  pinMode(PLAYER_4, OUTPUT);
  pinMode(PLAYER_2, OUTPUT);
  pinMode(PLAYER_1, OUTPUT);
  pinMode(PLAYER_BLANK, OUTPUT);
  pinMode(PLAYER_ALL, OUTPUT);
  pinMode(CPU_8, OUTPUT);
  pinMode(CPU_4, OUTPUT);
  pinMode(CPU_2, OUTPUT);
  pinMode(CPU_1, OUTPUT);
  pinMode(CPU_BLANK, OUTPUT);
  pinMode(CPU_ALL, OUTPUT);
}

void start(){
  WriteAll(CPU_DISPLAY);
  WriteAll(PLAYER_DISPLAY);
  delay(150);
  WriteNone(CPU_DISPLAY);
  WriteNone(PLAYER_DISPLAY);
  delay(150);
  WriteAll(CPU_DISPLAY);
  WriteAll(PLAYER_DISPLAY);
  delay(150);
  WriteNone(CPU_DISPLAY);
  WriteNone(PLAYER_DISPLAY);
  delay(150);
}

void cpuPlay() {
  cpuDisplayNumber = GenerateRamdomNumber();  
  WriteNone(CPU_DISPLAY);
  delay(150);
  WriteDigit(cpuDisplayNumber, CPU_DISPLAY);
}

int ConvertToDigit(int value)
{
  return value * 9 / 1000; 
}

void WriteDigit(int digit, int displayNumber)
{
  switch(digit)
  {
    case 0:
      WriteZero(displayNumber); 
    break;
    case 1:
      WriteOne(displayNumber);
    break;
    case 2:
      WriteTwo(displayNumber);
    break;
    case 3:
     WriteThree(displayNumber);
    break;
    case 4:
     WriteFour(displayNumber);
    break;
    case 5:
     WriteFive(displayNumber);
    break;
    case 6:
      WriteSix(displayNumber);
    break;
    case 7:
     WriteSeven(displayNumber);
    break;
    case 8:
     WriteEight(displayNumber);
    break;
    case 9:
     WriteNine(displayNumber);
    break;
  }
}

void blinkDisplay(int displayNumber)
{
   for(int i = 0; i < 5; i++) {
    WriteNone(displayNumber);
    delay(150);
    WriteAll(displayNumber);
    delay(150);
   }
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

void WriteAll(int displayNumber) {
  if (displayNumber == PLAYER_DISPLAY){
    digitalWrite(PLAYER_ALL, LOW); 
    digitalWrite(PLAYER_BLANK, HIGH); 
  }
  else {
    digitalWrite(CPU_ALL, LOW); 
    digitalWrite(CPU_BLANK, HIGH); 
  }
}

int GenerateRamdomNumber() {
  return random(0, 9);
}

void WriteNone(int displayNumber){
  if (displayNumber == PLAYER_DISPLAY){
    digitalWrite(PLAYER_BLANK, LOW); 
	digitalWrite(PLAYER_ALL, HIGH); 

  } else {  
    digitalWrite(CPU_BLANK, LOW); 
	digitalWrite(CPU_ALL, HIGH);
  }
}

void WriteZero(int displayNumber) {
    WriteNone(displayNumber);
    if (displayNumber == PLAYER_DISPLAY) {
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, LOW); 
    } else { 
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, LOW); 
    }
}

void WriteOne(int displayNumber) {
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, HIGH); 
    } else {    
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, HIGH); 
    }
}

void WriteTwo(int displayNumber){
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, HIGH); 
      digitalWrite(PLAYER_1, LOW); 
    } else { 
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH); 
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, HIGH); 
      digitalWrite(CPU_1, LOW); 
    }
}

void WriteThree(int displayNumber){
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, HIGH); 
      digitalWrite(PLAYER_1, HIGH); 
    } else {
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, HIGH); 
      digitalWrite(CPU_1, HIGH); 
    }
}

void WriteFour(int displayNumber) {
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, HIGH); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, LOW); 
    } else {  
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, HIGH); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, LOW); 
    }
}

void WriteFive(int displayNumber) {
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, HIGH); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, HIGH); 
    } else {  
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, HIGH); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, HIGH); 
    }
}

void WriteSix(int displayNumber) {
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, HIGH); 
      digitalWrite(PLAYER_2, HIGH); 
      digitalWrite(PLAYER_1, LOW); 
    } else {  
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, HIGH); 
      digitalWrite(CPU_2, HIGH); 
      digitalWrite(CPU_1, LOW); 
    }
}

void WriteSeven(int displayNumber) {
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, LOW);    
      digitalWrite(PLAYER_4, HIGH); 
      digitalWrite(PLAYER_2, HIGH); 
      digitalWrite(PLAYER_1, HIGH); 
    } else {    
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, LOW); 
      digitalWrite(CPU_4, HIGH); 
      digitalWrite(CPU_2, HIGH); 
      digitalWrite(CPU_1, HIGH); 
    }
}

void WriteEight(int displayNumber){
  WriteNone(displayNumber);
   if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, HIGH);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, LOW); 
    } else {   
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, HIGH); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, LOW); 
    }
}

void WriteNine(int displayNumber) {
  WriteNone(displayNumber);
  if (displayNumber == PLAYER_DISPLAY){
      digitalWrite(PLAYER_BLANK, HIGH); 
      digitalWrite(PLAYER_ALL, HIGH);
      digitalWrite(PLAYER_8, HIGH);    
      digitalWrite(PLAYER_4, LOW); 
      digitalWrite(PLAYER_2, LOW); 
      digitalWrite(PLAYER_1, HIGH); 
    } else {   
      digitalWrite(CPU_BLANK, HIGH); 
      digitalWrite(CPU_ALL, HIGH);
      digitalWrite(CPU_8, HIGH); 
      digitalWrite(CPU_4, LOW); 
      digitalWrite(CPU_2, LOW); 
      digitalWrite(CPU_1, HIGH); 
    }
}

void GameOver() {
  ShowPoints();
  interval = 3000;
  Reset();
  points = 0;
  missCounter = 0;
  resetTimer = true;
  cpuPlay();
}

void ShowPoints() {
  
   float fpoints = points;
   WriteDigit((fpoints / 10), 1); 
   WriteDigit(fmod(fpoints, 10), 2);   
   delay(5000);
}

void Reset(){
  WriteNone(CPU_DISPLAY);
  WriteNone(PLAYER_DISPLAY);
  delay(150);
  WriteAll(CPU_DISPLAY);
  WriteAll(PLAYER_DISPLAY);
  delay(150);
  WriteNone(CPU_DISPLAY);
  WriteNone(PLAYER_DISPLAY);
  delay(150);
  WriteAll(CPU_DISPLAY);
  WriteAll(PLAYER_DISPLAY);
  delay(150);
  WriteNone(CPU_DISPLAY);
  WriteNone(PLAYER_DISPLAY);
  delay(150);
}
