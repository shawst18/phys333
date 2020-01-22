void setup() {
  // put your setup code here, to run once:
 pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0; i<100; i++)  //Short Dashes for S
{
analogWrite(3, i);   // turn the LED on (HIGH is the voltage level)
  delay(30);
}
for(int i=100; i>0; i--)  //Short Dashes for S
{
analogWrite(3, i);   // turn the LED on (HIGH is the voltage level)
  delay(30);
}
}
