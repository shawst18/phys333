//program for reading an LM34 Temp sensor using an arduino

unsigned long t1;
int Sensvalue;
float voltage, temp;

void setup() {
  Serial.begin(9600);
  Serial.println("t(ms),\tADC value(0-1023),\tvoltage(0-5v),\t\ttemp.(F)");
}

void loop() {
  t1 = millis();  //Get time
  Sensvalue = analogRead(A0); //Get analog read value [0, 1023]
  voltage = (float)Sensvalue * (float)(5.0 / 1023.0); //Convert analog read value to voltage [0, 5]volts
  temp = voltage * 100; //Convert to temp in F., 10mv per degree F.
  Serial.print(t1);
  Serial.print(",\t");
  Serial.print(Sensvalue);
  Serial.print(",\t\t\t");
  Serial.print(voltage);
  Serial.print(",\t\t\t");
  Serial.println(temp);
  delay(500);
}
