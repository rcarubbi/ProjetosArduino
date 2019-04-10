#include <LiquidCrystal.h>

const int rs = 4, en = 3, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const char terminator = '\n';
void setup()
{
   Serial.begin(9600);
}

void loop()
{
   lcd.clear();
   lcd.print(Serial.readStringUntil(terminator));
   delay(1000);
}
