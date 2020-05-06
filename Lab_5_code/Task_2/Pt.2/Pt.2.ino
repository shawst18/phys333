/* This is the WEATHER-MAN (TM) System that updates a user on weather conditions. By Stephen Shaw
    Version: 1.0
    4 May 2020
*/
#include <LiquidCrystal.h> //Lcd display library
#include "Adafruit_Si7021.h" //temp sensor library

// link for lcd screen setup below
// https://learn.sparkfun.com/tutorials/basic-character-lcd-hookup-guide
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_Si7021 sensor = Adafruit_Si7021(); //Defind temp sensor

float temp, humid, maxTemp, maxHumid;
int i;

void setup() {
  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }
  Serial.println("Si7021 test!");
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  //Setup display analog to user
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("WEATHER-MAN (TM)");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("By Stephen Shaw");
  lcd.setCursor(0, 1);
  lcd.print("Version: 1.2");
  delay(4000);
}

void loop() {
    temp = (sensor.readTemperature() * (1.8)) + 32; //Read temp, Convert to Farenheit
    humid = sensor.readHumidity(); //Read Humidity
    if (i == 0)
    {
      maxTemp = temp;
      maxHumid = humid;
    }
    if (temp > maxTemp)
    {
      maxTemp = temp;
    }
    if (humid > maxHumid)
    {
      maxHumid = humid;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New Weather");
    lcd.setCursor(0, 1);
    lcd.print("Update");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("temp: ");
    lcd.print(temp);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humid: ");
    lcd.print(humid);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Max Temp: ");
    lcd.print(maxTemp);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Max Humid: ");
    lcd.print(maxHumid);
    delay(3000);
    i++;
}
