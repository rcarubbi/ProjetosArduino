#define PLAYER_DISPLAY 2
#define CPU_DISPLAY 1
 
int vRS[2] = {2, 14};
int hSup[2]= {3, 15};
int vLS[2]= {4, 16};
int hMid[2]= {5, 17};
int point[2]= {6, 18};
int vRL[2]= {7, 19};
int hLow[2]= {8, 20};
int vLL[2]= {9, 21};

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
  setOutput(CPU_DISPLAY);
  setOutput(PLAYER_DISPLAY);
  start();
  cpuPlay();       
}

void loop() {
   potValue = analogRead(potPin);
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

void setOutput(int displayNumber)
{
  pinMode(hSup[displayNumber-1], OUTPUT);
  pinMode(hMid[displayNumber-1], OUTPUT);
  pinMode(hLow[displayNumber-1], OUTPUT);
  pinMode(vLS[displayNumber-1], OUTPUT);
  pinMode(vLL[displayNumber-1], OUTPUT);
  pinMode(vRS[displayNumber-1], OUTPUT);
  pinMode(vRL[displayNumber-1], OUTPUT);
  pinMode(point[displayNumber-1], OUTPUT);
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
    digitalWrite(hSup[displayNumber-1], HIGH);    
    digitalWrite(hMid[displayNumber-1], HIGH);   
    digitalWrite(hLow[displayNumber-1], HIGH);  
    digitalWrite(vLS[displayNumber-1], HIGH); 
    digitalWrite(vLL[displayNumber-1], HIGH);  
    digitalWrite(vRS[displayNumber-1], HIGH);  
    digitalWrite(vRL[displayNumber-1], HIGH); 
    digitalWrite(point[displayNumber-1], HIGH);
}

int GenerateRamdomNumber() {
  return random(0, 9);
}

void WriteNone(int displayNumber){
    digitalWrite(hSup[displayNumber-1], LOW);    
    digitalWrite(hMid[displayNumber-1], LOW);   
    digitalWrite(hLow[displayNumber-1], LOW);  
    digitalWrite(vLS[displayNumber-1], LOW); 
    digitalWrite(vLL[displayNumber-1], LOW);  
    digitalWrite(vRS[displayNumber-1], LOW);  
    digitalWrite(vRL[displayNumber-1], LOW); 
    digitalWrite(point[displayNumber-1], LOW);
}

void WriteZero(int displayNumber) {
    WriteNone(displayNumber);
    digitalWrite(hSup[displayNumber-1], HIGH);
    digitalWrite(hLow[displayNumber-1], HIGH);
    digitalWrite(vLS[displayNumber-1], HIGH);
    digitalWrite(vLL[displayNumber-1], HIGH);
    digitalWrite(vRS[displayNumber-1], HIGH);
    digitalWrite(vRL[displayNumber-1], HIGH);
}

void WriteOne(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
}

void WriteTwo(int displayNumber){
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH); 
  digitalWrite(vLL[displayNumber-1], HIGH); 
  digitalWrite(hLow[displayNumber-1], HIGH);
}

void WriteThree(int displayNumber){
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH); 
  digitalWrite(vRL[displayNumber-1], HIGH); 
  digitalWrite(hLow[displayNumber-1], HIGH);
}

void WriteFour(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(hMid[displayNumber-1], HIGH);  
  digitalWrite(vLS[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
}

void WriteFive(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH); 
  digitalWrite(vLS[displayNumber-1], HIGH); 
  digitalWrite(hLow[displayNumber-1], HIGH);
}

void WriteSix(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(hLow[displayNumber-1], HIGH);
  digitalWrite(vLL[displayNumber-1], HIGH);
  digitalWrite(vLS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH);  
}

void WriteSeven(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
}

void WriteEight(int displayNumber){
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(hLow[displayNumber-1], HIGH);
  digitalWrite(vLS[displayNumber-1], HIGH);
  digitalWrite(vLL[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH);  
}

void WriteNine(int displayNumber) {
  WriteNone(displayNumber);
  digitalWrite(hSup[displayNumber-1], HIGH);
  digitalWrite(hLow[displayNumber-1], HIGH);
  digitalWrite(vLS[displayNumber-1], HIGH);
  digitalWrite(vRL[displayNumber-1], HIGH);
  digitalWrite(vRS[displayNumber-1], HIGH);
  digitalWrite(hMid[displayNumber-1], HIGH);  
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















