/*
   Code for reading two sensors, turning on and off IR light for infant if they agree.
   Some adjustment necessary in defining both sensors. Done with only one
   sensor defined
*/

#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor1 = Adafruit_Si7021(); //Define Sensor1
Adafruit_Si7021 sensor2 = Adafruit_Si7021(); //Define Sensor2

int t0;

void setup() {
  Serial.begin(115200);

  // wait for serial port to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Si7021 test!");

  if (!sensor1.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      ;
  }

  t0 = millis();
  pinMode(2, OUTPUT); //Pin of IR light
  pinMode(3, OUTPUT); //Pin of Error sensors don't match light
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void loop() {

  float temp1 = (sensor1.readTemperature() * (1.8)) + 32; //Convert to Farenheit
  float temp2 = (sensor2.readTemperature() * (1.8)) + 32; //Convert to Farenheit
  if (temp1 = temp2)
  {
    if (temp1 > 98.0)
    {
      digitalWrite(2, HIGH);
    }
    if (temp1 > 100.0)
    {
      digitalWrite(2, LOW);
    }
  }
  if (temp1 != temp2)
  {
    digitalWrite(3, HIGH);
  }
  delay(1000);
}
