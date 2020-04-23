void setup() {
  // put your setup code here, to run once:
  for (int t = 1; t < 14; t++)
  {
    pinMode(t, OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  int i = random(1, 13);
  for (int j = 0; j < 50; j++)
  {
    digitalWrite( i, HIGH);
    delayMicroseconds(5000);
    digitalWrite( i, LOW);
    delayMicroseconds(10000 - 5000);
  }
  for (int j = 0; j < 50; j++)
  {
    digitalWrite( i - 1, HIGH);
    digitalWrite( i + 1, HIGH);
    digitalWrite( i, HIGH);
    delayMicroseconds(300);
    digitalWrite( i - 1, LOW);
    digitalWrite( i + 1, LOW);
    digitalWrite( i, LOW);
    delayMicroseconds(10000 - 300);
  }
  for (int j = 0; j < 50; j++)
  {
    digitalWrite( i + 2, HIGH);
    digitalWrite( i - 2, HIGH);
    digitalWrite( i - 1, HIGH);
    digitalWrite( i + 1, HIGH);
    delayMicroseconds(50);
    digitalWrite( i + 2, LOW);
    digitalWrite( i - 2, LOW);
    digitalWrite( i - 1, LOW);
    digitalWrite( i + 1, LOW);
    delayMicroseconds(10000 - 50);
  }
  for (int j = 0; j < 50; j++)
  {
    digitalWrite( i + 3, HIGH);
    digitalWrite( i - 3, HIGH);
    delayMicroseconds(1);
    digitalWrite( i + 3, LOW);
    digitalWrite( i - 3, LOW);
    delayMicroseconds(10000 - 1);
  }
  int j = random(500, 3000);
  delay(j);
}
