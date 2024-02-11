//prime arduino

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

long val;
long value;
long pass = 0;
int pMeterVal = 0;
int servoVal = 0;
int c = 0;
long curTime;
long pause;
long bTime;
long elaps;

Servo servo_A3;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
int LCDRow = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 4, 3, 2, A4, A5);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A3, OUTPUT);

  servo_A3.attach(A3);
  servo_A3.write(0);
  
  value= random(0, 9999);
  
  //sending random number thorugh serial port
  Serial.write(value / 256);
  Serial.write(value % 256);
  
  pause = 5000;
  elaps = 0;
  bTime = millis();

}

void loop() {
  
  if (elaps >= pause){
    
    value = random(0, 9999);
    //sending random number thorugh serial port
    Serial.write(value / 256);
  	Serial.write(value % 256);

    pass = 0;
    lcd.clear();
    c = 0;
    
     elaps = 0;
     bTime = millis();
  }

  curTime = millis();
  elaps = curTime - bTime;
  
  long key = keypad.getKey();

    if(key) {
      if (key == 68){
        //deliting all digits
        c = 0;
        pass = 0;
        lcd.clear();
      }
      else if (key == 67){
        //deliting digit
        pass = pass / 10; 
        c--;
        lcd.clear();
        lcd.setCursor(0, 1);
        //printing stars
        for(int i = 0; i < c; i++){
          lcd.print("*");
        }
      }
  
      else {
        c++;
        lcd.clear();
        lcd.setCursor(0, 1);
        //printing stars
        for(int i = 0; i < c; i++){
          lcd.print("*");
        }
      key = key - 48;
      pass = (pass * 10) + key;
      }
    }
  

  if(value == pass){
    lcd.setCursor(0, 0);
    lcd.print("   Unlocked   ");
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
    pMeterVal = analogRead(A2);
    servoVal = map(pMeterVal, 0, 1023, 0, 89);
    servo_A3.write(servoVal);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("   Enter Key   ");
    digitalWrite(13,LOW);
    digitalWrite(12,HIGH);
  } 
  
} 