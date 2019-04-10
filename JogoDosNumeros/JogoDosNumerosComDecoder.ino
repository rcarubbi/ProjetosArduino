#define PLAYER_DISPLAY 2
#define CPU_DISPLAY 1

#define PLAYER_8 9
#define PLAYER_4 8
#define PLAYER_2 7
#define PLAYER_1 6
#define PLAYER_BLANK 12
#define PLAYER_ALL 13

#define CPU_8 5
#define CPU_4 4
#define CPU_2 2
#define CPU_1 3
#define CPU_BLANK 10
#define CPU_ALL 11

#define POT_PIN A0

int potValue = 0; 

int playerDisplayNumber = 0;
int cpuDisplayNumber = 0;

int points = 0;
int missCounter = 0;

long previousMillis = 0; 
long interval = 3000;
bool resetTimer = false;

void setup() { 
  Serial.begin(9600);
  setOutputPins();
  reset();
  cpuPlay();       
 
}

void loop() {
   potValue = analogRead(POT_PIN);
   analogWrite(3, points);
   analogWrite(9, missCounter);
   playerDisplayNumber = map(potValue,0,1023,0,9);
  
    
   writeDigit(playerDisplayNumber, PLAYER_DISPLAY);   
   if (playerDisplayNumber == cpuDisplayNumber)
   {
      points++;
      Serial.println("Hit! - Score:" + String(points));
      blinkDisplay(CPU_DISPLAY);
      cpuPlay();   
      resetTimer = true;
      interval = interval - 100;
      Serial.println("New time:" + String(interval));
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
   delay(200);
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
 

void cpuPlay() {
  cpuDisplayNumber = generateRamdomNumber();  
  writeNone(CPU_DISPLAY);
  delay(150);
  writeDigit(cpuDisplayNumber, CPU_DISPLAY);
}

void writeDigit(int digit, int displayNumber)
{
  switch(digit)
  {
    case 0:
      writeZero(displayNumber); 
    break;
    case 1:
      writeOne(displayNumber);
    break;
    case 2:
      writeTwo(displayNumber);
    break;
    case 3:
      writeThree(displayNumber);
    break;
    case 4:
      writeFour(displayNumber);
    break;
    case 5:
      writeFive(displayNumber);
    break;
    case 6:
      writeSix(displayNumber);
    break;
    case 7:
      writeSeven(displayNumber);
    break;
    case 8:
      writeEight(displayNumber);
    break;
    case 9:
      writeNine(displayNumber);
    break;
  }
}

void blinkDisplay(int displayNumber)
{
   for(int i = 0; i < 5; i++) {
      writeNone(displayNumber);
      delay(150);
      writeAll(displayNumber);
      delay(150);
   }
}

void checkMiss()
{
    if (missCounter < 3) {
      cpuPlay();
      missCounter++;
      Serial.println("Time over");
      Serial.println("Miss: " + String(missCounter));
    }
    else {
       gameOver();
    } 
}

void writeAll(int displayNumber) {
  if (displayNumber == PLAYER_DISPLAY){
    digitalWrite(PLAYER_ALL, LOW); 
    digitalWrite(PLAYER_BLANK, HIGH); 
  }
  else {
    digitalWrite(CPU_ALL, LOW); 
    digitalWrite(CPU_BLANK, HIGH); 
  }
}

int generateRamdomNumber() {
  return random(0, 9);
}

void writeNone(int displayNumber){
  if (displayNumber == PLAYER_DISPLAY){
    digitalWrite(PLAYER_BLANK, LOW); 
	digitalWrite(PLAYER_ALL, HIGH); 
  } else {  
    digitalWrite(CPU_BLANK, LOW); 
	digitalWrite(CPU_ALL, HIGH);
  }
}

void writeZero(int displayNumber) {
    writeNone(displayNumber);
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

void writeOne(int displayNumber) {
   writeNone(displayNumber);
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

void writeTwo(int displayNumber){
   writeNone(displayNumber);
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

void writeThree(int displayNumber){
   writeNone(displayNumber);
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

void writeFour(int displayNumber) {
   writeNone(displayNumber);
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

void writeFive(int displayNumber) {
   writeNone(displayNumber);
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

void writeSix(int displayNumber) {
   writeNone(displayNumber);
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

void writeSeven(int displayNumber) {
   writeNone(displayNumber);
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

void writeEight(int displayNumber){
   writeNone(displayNumber);
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

void writeNine(int displayNumber) {
  writeNone(displayNumber);
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

void gameOver() {
  showPoints();
  interval = 3000;
  reset();
  points = 0;
  missCounter = 0;
  resetTimer = true;
  cpuPlay();
}

void showPoints() {
   Serial.println("Score: " + String(points));
   float fpoints = points;
   writeDigit((fpoints / 10), 2); 
   writeDigit(fmod(fpoints, 10), 1);   
   delay(5000);
}

void reset(){
  Serial.println("New Game");
  writeNone(CPU_DISPLAY);
  writeNone(PLAYER_DISPLAY);
  delay(150);
  writeAll(CPU_DISPLAY);
  writeAll(PLAYER_DISPLAY);
  delay(150);
  writeNone(CPU_DISPLAY);
  writeNone(PLAYER_DISPLAY);
  delay(150);
  writeAll(CPU_DISPLAY);
  writeAll(PLAYER_DISPLAY);
  delay(150);
  writeNone(CPU_DISPLAY);
  writeNone(PLAYER_DISPLAY);
  delay(150);
}
