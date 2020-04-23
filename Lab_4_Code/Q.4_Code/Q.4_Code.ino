/* This code is meant to take temperature readings from a Adafruit temp sensor and compare them
   to determine whether the readings have stabalized enough for satisfactory uncertainty in the
   number provided to the user via an lcd crystal display. The certainty can be changed by adjusting
   the difference spec between each temp readings that the algorithm reads as being in agreeance
   and the amount of consecutive pairs of readings need to be in agreeance for the algorithm to provide
   a final reading of temperature to the user. Code written by Stephen Shaw
*/
#include <LiquidCrystal.h> //Lcd display library
#include "Adafruit_Si7021.h" //temp sensor library

// link for lcd screen setup below
// https://learn.sparkfun.com/tutorials/basic-character-lcd-hookup-guide
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_Si7021 sensor = Adafruit_Si7021(); //Defind temp sensor

int i = 0; //Counter
int k = 0; //Comparitor value
float T1, T2; //Values for comparing temperature

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
  lcd.print("Sensor Ready");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");
  lcd.setCursor(0, 1);
  lcd.print("On Sensor");
}

void loop() {
  int j = i % 2; //check if counter is on odd or even, change j to determine if it is filling T1 or T2 with the next reading
  if (j == 0) //If the counter is odd, fill T1
  {
    T1 = (sensor.readTemperature() * (1.8)) + 32; //Convert to Farenheit, fill T1 with new reading
  }
  if (j == 1) //If the counter is even, fill T2
  {
    T2 = (sensor.readTemperature() * (1.8)) + 32; //Convert to Farenheit, fill T2 with new reading
  }
  /* the variable temp takes the last two readings and averages them. Once the temp is determined to be stable,
      this will be the value provided to the user. So when a value is reported, it is the average of the last
      two temp readings taken by the sensor
  */
  float temp = (T1 + T2) / 2;
  // Below prints dialog to the user, communicating the taking temperature state
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Now taking");
  lcd.setCursor(0, 1);
  lcd.print("temperature...");
  if (abs(T1 - T2) < 0.02) //Compare temp readings, add one to k if difference is less than 0.02
  {
    k = k + 1;
  }
  /*
     Compare temp readings, reset k to zero if difference is greater than 0.02
     k is set to zero to ensure that k is only counted to how many consecutive reading pairs are less than 0.02
  */
  if (abs(T1 - T2) > 0.02)
  {
    k = 0;
  }
  if (k == 3)                     //This value can be adjusted depending on time you want algorithm to run versus how certain you want the temp reading to be
  {
    // Print dialog to user if value is determined stable, provides reading to user for 7 seconds before resetting
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("temp: ");
    lcd.print(temp);
    delay(7000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("now reseting");
    k = 0;
  }
  i = i + 1; // add one to the counter
  delay(1000); //delay 1 second between temp readings
}
