void setup() {
  for (int t = 1; t < 14; t++)
  {
    pinMode(t, OUTPUT);
  }
}

void loop() {
  for (int j = 0; j < 100; j++)
  {
    digitalWrite( 3, HIGH);
    delayMicroseconds(j);
    digitalWrite( 3, LOW);
    delayMicroseconds(10000 - j);
  }
   for (int j =  100; j > 0; j--)
  {
    digitalWrite( 3, HIGH);
    delayMicroseconds(j);
    digitalWrite( 3, LOW);
    delayMicroseconds(10000 - j);
  }
}
