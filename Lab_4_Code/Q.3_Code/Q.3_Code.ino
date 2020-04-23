#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

int state;

void setup() {
  Serial.begin(9600);

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

  pinMode(2, OUTPUT); //Rice Cooker voltage pin
  state = 1; //Initialize system state to 1
}

void loop() {
  float temp = (sensor.readTemperature() * (1.8)) + 32; //Convert to Farenheit
  if (temp > 212)
  {
    state = 2;
  }
  int pwr1 = 1000; //Define voltage needed to power rice cooker on high, input [0,1000] corresponding to out [0, 5] Volts
  int pwr2 = 500; //Define voltage for simmer state, input [0,1000] corresponding to [0,5] Volts
  if (state == 1)
  {
      pwm(1000, pwr1, 1, 2);
  }
  if (state == 2)
  {
      pwm(1000, pwr2, 1, 2);
  }
}


// Imported PWM function from Lab 2
void pwm(int dur, int power, int per, int in) {
  /*  int dur: duration of the power supply, in ms
      int power: The ratio of power desired, out of 1000
      int per: the period of oscillatin between low and high (How long between each "flicker")
      int in: the input pin desired for power supply
  */
  for (int k = 0; k < dur / per ; k++)
  {
    digitalWrite( in, HIGH);
    delayMicroseconds(power * per);
    digitalWrite( in, LOW);
    delayMicroseconds((1000 - power) * per);
  }
  return;
}
