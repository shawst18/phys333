/* Finding and reporting speed and overall distance traveled on a trip to an LCD screen using a LSM9DS1 sensor
    Developed using code from SparkFun Electrons as cited below.
    Version 2.0
    Stephen Shaw
    4 May 2020
*/

#include <LiquidCrystal.h> //Lcd display library
// link for lcd screen setup below
// https://learn.sparkfun.com/tutorials/basic-character-lcd-hookup-guide
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*****************************************************************
  LSM9DS1_Basic_I2C.ino
  SFE_LSM9DS1 Library Simple Example Code - I2C Interface
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: April 30, 2015
  https://github.com/sparkfun/LSM9DS1_Breakout

  The LSM9DS1 is a versatile 9DOF sensor. It has a built-in
  accelerometer, gyroscope, and magnetometer. Very cool! Plus it
  functions over either SPI or I2C.

  This Arduino sketch is a demo of the simple side of the
  SFE_LSM9DS1 library. It'll demo the following:
  How to create a LSM9DS1 object, using a constructor (global
  variables section).
  How to use the begin() function of the LSM9DS1 class.
  How to read the gyroscope, accelerometer, and magnetometer
  using the readGryo(), readAccel(), readMag() functions and
  the gx, gy, gz, ax, ay, az, mx, my, and mz variables.
  How to calculate actual acceleration, rotation speed,
  magnetic field strength using the calcAccel(), calcGyro()
  and calcMag() functions.
  How to use the data from the LSM9DS1 to calculate
  orientation and heading.

  Hardware setup: This library supports communicating with the
  LSM9DS1 over either I2C or SPI. This example demonstrates how
  to use I2C. The pin-out is as follows:
  LSM9DS1 --------- Arduino
   SCL ---------- SCL (A5 on older 'Duinos')
   SDA ---------- SDA (A4 on older 'Duinos')
   VDD ------------- 3.3V
   GND ------------- GND
  (CSG, CSXM, SDOG, and SDOXM should all be pulled high.
  Jumpers on the breakout board will do this for you.)

  The LSM9DS1 has a maximum voltage of 3.6V. Make sure you power it
  off the 3.3V rail! I2C pins are open-drain, so you'll be
  (mostly) safe connecting the LSM9DS1's SCL and SDA pins
  directly to the Arduino.

  Development environment specifics:
  IDE: Arduino 1.6.3
  Hardware Platform: SparkFun Redboard
  LSM9DS1 Breakout Version: 1.0

  This code is beerware. If you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*****************************************************************/
// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
// #define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
// #define LSM9DS1_AG 0x6B // Would be 0x6A if SDO_AG is LOW

////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract
// a declination to get a more accurate heading. Calculate
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

//Function definitions
void printGyro();
void printAccel();
void printMag();
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);

void setup()
{
  Serial.begin(115200);

  Wire.begin();

  if (imu.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }
  //Setup display analog to user
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Trip Buddy");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("By Stephen Shaw");
  lcd.setCursor(0, 1);
  lcd.print("Version: 2.0");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("This will Report");
  lcd.setCursor(0, 1);
  lcd.print("Velocity");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("and Distance");
  delay(2000);
}

float v0, v, d0, d, t1, mag_a, mag_a2, sum_a; //Declare variables
int k; //for counting when to report distance traveled

void loop()
{
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // To read from the accelerometer, first call the
    // readAccel() function. When it exits, it'll update the
    // ax, ay, and az variables with the most current data.
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    // To read from the magnetometer, first call the
    // readMag() function. When it exits, it'll update the
    // mx, my, and mz variables with the most current data.
    imu.readMag();
  }
  v0 = v; //make last interval velocity new initial velocity in calculations
  d0 = d; //make last distance value new initial distance value in calculations
  float ax1 = imu.calcAccel(imu.ax) - 0.14;
  float ay1 = imu.calcAccel(imu.ay);
  float az1 = imu.calcAccel(imu.az) - 1.0;
  sum_a = az1 + ax1 + ay1;
  mag_a = (sqrt(ax1 * ax1 + ay1 * ay1 + az1 * az1) - 0.024) * 9.8; //Magnitude in m/s^2
  if (mag_a < 2.0) mag_a = 0; //if acceleration is too small, change acceleration to zero since stationary
  if (sum_a < 0) mag_a = mag_a * -1; //if acceleration is in negative direction, make acceleration negative for de-acceleration
  t1 = 0.5; //0.5 second approximation between readings
  v = mag_a * t1 + v0; //Calculate speed in m/s
  if (v < 0) v = 0; //Sorry. Can't  drive reverse for long periods in this program
  mag_a2 = mag_a;
  if (mag_a2 < 0) mag_a2 = 0; // ensure acceleration can't be negative in the distance calculation
  d = d0 + v0 * t1 + 0.5 * mag_a2 * t1 * t1; //Calculate distance traveled in meters
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vel (m/s)");
  lcd.setCursor(11, 0);
  lcd.print(v);
  lcd.setCursor(0, 1);
  lcd.print("Dist (m)");
  lcd.setCursor(11, 1);
  lcd.print(d);
  delay(500);
  /* used as a basic time metric in calculations. Although this will add some uncertainty due to the
     amount of time calculations take, this will still give a rough idea of the time intervals between
     each reading to use in the calculations.
  */

}
