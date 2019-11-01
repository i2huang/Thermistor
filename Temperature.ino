// Uncomment the include files for the I2C LCD
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <math.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

// LCD connections:
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define NTC_BIAS 2    // D2

void setup() {
  // LCD initialization:
  // set up the LCD's number of columns and rows:
  // lcd.begin(16, 2);
  // lcd.backlight();

  // initialize the serial communications:
  Serial.begin(9600);
  pinMode(NTC_BIAS, OUTPUT);
  digitalWrite(NTC_BIAS, 1);
}

void loop() {
  int rawADC;
  unsigned int mV;
  unsigned long x;
  float Rt;
  float Temp;
  
  delay(1000);
  rawADC = analogRead(A0);
  x = rawADC;
  // Convert ADC reading into mV
  mV = x;			// Task 1: Convert x into mV

  // Calculate Rt
  Rt = mV;			// Task 2: Convert mV into Thermistor resistance Rt

  // Calculate Temp
  Temp = 1/3950.0 * log (Rt / 50000.0);
  Temp = 1.0/( Temp + 1.0 / (25+273)) - 273;
  
  Serial.print("mV: ");
  Serial.println(mV);
  Serial.print("Rt: ");
  Serial.println(Rt);
  Serial.print("Temp: ");
  Serial.println(Temp);

/* LCD write 
  lcd.clear();
  
  lcd.print("V:");
  lcd.print(mV);
  lcd.print("mV");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(Temp);
  lcd.print("C");
  */ 
}
