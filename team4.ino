// millis를 초기화 해주기 위해 선언
extern volatile unsigned long timer0_millis;

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,2,3,4,5);

int piezo = 9;
int sonic_ec = 10, sonic_tr = 13;
int btn = 8;

//int intervalTime = 180; // 3분 간격으로 한다.
int intervalTime = 10; // 테스트를 위해 10초 간격으로 한다.

bool isPiezo = false; // 현재 피에조가 재생되고 있는지 체크하는 변수
int level = 1;

void setup()
{
  	Serial.begin(9600);
  
    lcd.begin(18,2);

    // 초음파
    pinMode(sonic_tr,OUTPUT);
    pinMode(sonic_ec,INPUT);
  
  	reset();
}

void loop()
{
    if(checkDistance()){
        updateLCD();
      
        if(1<=currentS() && (int)(currentS() % intervalTime) == 0 && !isPiezo){
    		Serial.println("piezo!");
          	isPiezo = true;
          
            tone(piezo, level*40,1000); // 피에조 부저 소리
          	level++;
        }else if((int)(currentS() % intervalTime) != 0){
          isPiezo = false;
        }
        
    }else{
        reset();
    }
  
    // 사용자가 버튼을 누르면 초기화
    if (digitalRead(btn) == HIGH) {
      reset();
    }
}

// 선언된 변수를 초기화하는 함수
void reset(){
    Serial.println("RESET");
  
    lcd.clear();
  	timer0_millis = 0; // millis() 초기화
  	noTone(piezo); // 피에조 부저 소리 중지
  	level = 1; // 레벨 초기화
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

    return distnce <= 25;
}

// 시간 표시 (매 1초마다 업데이트)
void updateLCD(){  
    lcd.setCursor(0, 0);
    lcd.print("AccTime:"); //누적된 시간
    lcd.print(convertTime(currentS()));
  

    lcd.setCursor(0, 1);
    lcd.print("NextAlarm:"); //잔여시간
    lcd.print(convertTime(intervalTime - currentS() % intervalTime));
}

// 현재 시간을 초단위로 변환해주는 함수
int currentS(){
  return (int)(millis()/1000);
}

// 초 > 분초 로 변환해주는 함수
String convertTime(int _s){
  int conM = _s / 60;
  String sM = conM < 10 ? "0"+(String)conM : (String)conM;
  
  int conS = _s % 60;
  String sS = conS < 10 ? "0"+(String)+conS : (String)conS;
  
  return sM+"m"+sS+"s";
}