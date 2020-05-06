/* Code for aquiring data for temp and humidity. By Stephen Shaw
    Version: 1.0
    4 May 2020
*/
#include "Adafruit_Si7021.h" //temp sensor library

Adafruit_Si7021 sensor = Adafruit_Si7021(); //Defind temp sensor

float temp, humid;
int t0, t1;

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
  Serial.begin(9600);
  t0 = millis();
}

void loop() {
  t1 = millis() - t0;
  temp = (sensor.readTemperature() * (1.8)) + 32; //Read temp, Convert to Farenheit
  humid = sensor.readHumidity(); //Read Humidity
  Serial.print(t1);
  Serial.print(" ");
  Serial.print("\t");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print("\t");
  Serial.print(humid);
  Serial.println(" ");
  delay(5000);
}
