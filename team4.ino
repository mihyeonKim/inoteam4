#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,2,3,4,5);

int piezo = 9;
int sonic_ec = 10, sonic_tr = 13;
int btn = 8;

void setup()
{
    lcd.begin(16,2);
    pinMode(10,OUTPUT);
}

void loop()
{
    // LCD TEST
    // lcd.setCursor(0,1);
    // lcd.print("Hello World!");

    // 피에조 TEST
    // analogWrite(10,64);
    // analogWrite(10,0);
    
    // 초음파 TEST
    // if (duration==0) return;
    // long distnce=duration / 58.2;
    // if (distnce<25){
    //     lcd.setCursor(0,1);
    //     lcd.print("Hello World!");
    // }
}
