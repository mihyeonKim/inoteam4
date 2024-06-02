#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,2,3,4,5);

int piezo = 9;
int sonic_ec = 10, sonic_tr = 13;
int btn = 8;

void setup()
{
  	Serial.begin(9600);
  
    lcd.begin(16,2);

    // 초음파
    pinMode(sonic_tr,OUTPUT);
    pinMode(sonic_ec,INPUT);
}

void loop()
{
    // LCD TEST
    // lcd.setCursor(0,1);
    // lcd.print("Hello World!");

    // 피에조 TEST
    // analogWrite(piezo,64);
    // analogWrite(piezo,0);
    
    // 초음파 TEST
    // long duration=pulseIn(sonic_ec,HIGH);
    // if (duration==0) return;
    // long distnce=duration / 58.2;
    // if (distnce<25){
    //     lcd.setCursor(0,1);
    //     lcd.print("Hello World!");
    // }

    if(checkDistance()){
      	lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Hello World!");
    }else{
      	lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("NOT");
    }
}

// 초음파 센서로 거리를 측정하여 25이하의 데이터가 들어오면 bool을 반환하는 함수
// <= 25 : TRUE
bool checkDistance(){
  
    digitalWrite(sonic_tr,HIGH);
    delayMicroseconds(10);
    digitalWrite(sonic_tr,LOW);

    long duration = pulseIn(sonic_ec,HIGH);
    if ( duration == 0 ) return false;
    long distnce = duration / 58.2;
  
  	Serial.println(distnce);

    return distnce <= 25;
}
