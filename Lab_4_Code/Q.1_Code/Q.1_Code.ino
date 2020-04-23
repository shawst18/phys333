#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

int t0;

void setup() {
  Serial.begin(115200);

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

  t0 = millis();
  pinMode(2, OUTPUT); //Pin of IR heating lamp
  digitalWrite(2, LOW); //Turn heater off initially
}

void loop() {
  int t1 = millis() - t0;
  float temp = (sensor.readTemperature() * (1.8)) + 32; //Convert to Farenheit
  if (temp > 98.0)
  {
    digitalWrite(2, HIGH); //Turn Heater on if temp is greater than 98.0
  }
  if (temp > 100.0)
  {
    digitalWrite(2, LOW); //Turn Heater off if temp is greater than 100.0
  }
  delay(1000);
}
