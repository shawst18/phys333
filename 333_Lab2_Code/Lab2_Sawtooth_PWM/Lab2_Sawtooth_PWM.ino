void setup() {
  for (int t = 1; t < 14; t++)
  {
    pinMode(t, OUTPUT);
  }
}

void loop() {
      pwm(10, 500, 5, 3);
 for (int i = 0; i <= 1000; i += 50)
  {
    pwm(10, i, 5, 3);
  }
}


//FUNCTIONS
void pwm(int dur, int power, int per, int in) {
  /*  int dur: duration of the power supply (ms)
      int power: The ratio of power desired, out of 1000
      int per: the period of oscillation , full cycle between low and high (us)
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
