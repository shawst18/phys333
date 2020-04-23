void setup() {
  for (int t = 1; t < 14; t++)
  {
    pinMode(t, OUTPUT);
  }
}

void loop() {
  int i =200;
    pwm(1, i, 1, 2);





}

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
