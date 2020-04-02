
unsigned long t1;
int Sensvalue;
float voltage, temp;

void setup() {
  Serial.begin(9600);
  Serial.println("t(ms),\tADC value(0-1023),\tvoltage(0-5v),\t\ttemp.(F)");
}

void loop() {
  t1 = millis();
  Sensvalue = analogRead(A0);
  voltage = (float)Sensvalue * (float)(5.0 / 1023.0);
  temp = voltage * 100;
  Serial.print(t1);
  Serial.print(",\t");
  Serial.print(Sensvalue);
  Serial.print(",\t\t\t");
  Serial.print(voltage);
  Serial.print(",\t\t\t");
  Serial.println(temp);
  delay(500);
}
