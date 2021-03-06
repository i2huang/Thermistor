// Uncomment the include files for the I2C LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

// LCD connections:
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define NTC_BIAS 2    // D2

void setup() {
  // LCD initialization:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.backlight();

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
  float log_Rt;
  float Temp;
  
  delay(1000);
  rawADC = analogRead(A0);
  x = rawADC;
  // Convert ADC reading into mV
  x = 5000 * x / 1023;

  // Calculate Rt
  Rt = 42000.0 / (5000.0 / mV - 1.0) / 1000.0;
  log_Rt = log(Rt);

  // Calculate Temperature in K
  Temp = 401 - 28 * log_Rt + 0.1 * pow(log_Rt, 3);

  // Calculate Temperature in C
  Temp = Temp - 273.15;
  
  Serial.print("mV: ");
  Serial.println(mV);
  Serial.print("Rt: ");
  Serial.println(Rt);
  Serial.print("Temp: ");
  Serial.println(Temp);

// LCD write 
  lcd.clear();
  
  lcd.print("V:");
  lcd.print(mV);
  lcd.print("mV");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(Temp);
  lcd.print("C");
}
