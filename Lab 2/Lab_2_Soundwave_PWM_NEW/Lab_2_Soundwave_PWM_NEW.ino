void setup() {
  Serial.begin(9600);
  for (int t = 1; t < 14; t++)
  {
    pinMode(t, OUTPUT);
  }
  //Serial.print(sin(M_PI));
}
int t0 = millis();
void loop() {
  int f = 40; //[20,1000] 
  int T = 1000 / f;
  float w = 0.002 * M_PI * f;
  float tstep;
  float t1;
  t1 = (float)((millis() - t0) % T);
  int power = (sin(w * t1) + 1) * 500;
  pwm(1, power, 1, 3);
  //Serial.print(power);
  //Serial.print(" ");
}

//FUNCTIONS
void pwm(int dur, int power, int per, int in) {
  /*  int dur: duration of the power supply (ms, [1,1000])
      int power: The ratio of power desired, out of 1000
      int per: the period of oscillation , full cycle between low and high (us [5-20])
      int in: the input pin desired for power supply
  */
  for (int k = 0; k <  100 * dur / per ; k++)
  {
    digitalWrite( in, HIGH);
    delayMicroseconds(power * per);
    digitalWrite( in, LOW);
    delayMicroseconds((1000 - power) * per);
  }
  return;
}
