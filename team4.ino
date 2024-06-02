#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,2,3,4,5);

int piezo = 9;
int sonic_ec = 10, sonic_tr = 13;
int btn = 8;

void setup()
{
    lcd.begin(16,2);
}

void loop()
{
    lcd.setCursor(0,1);
    lcd.print("Hello World!");
}
