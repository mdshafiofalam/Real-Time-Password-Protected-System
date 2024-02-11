//Mobile arduino

// include the library code:
#include <LiquidCrystal.h>

long val;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	//initlized serial library
    Serial.begin(9600);
  	// set up the LCD's number of columns and rows:
  	lcd.begin(16, 2);
}

void loop() {
	//getting value
	while (!Serial.available()){}
	byte b1 = Serial.read();
  	
	while (!Serial.available()){}
	byte b2 = Serial.read();

  	val = b1 * 256 + b2 ;
	//printing to lcd
	lcd.setCursor(0 , 0);
	lcd.print(val);
}
 