void setup() {
  // put your setup code here, to run once:
 pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0; i<3; i++)  //Short Dashes for S
{
digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
  }
  delay(750); //delay between letters, 3 time units

for(int i=0; i<3; i++)  // Long Dashes for O
{
digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
  }
  delay(750); //delay between letters, 3 time units

  for(int i=0; i<3; i++)   //Short Dashes for S
  {
digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
  delay(250);
  }
  
  delay(1750);    //Delay between, 7 time units, plays message again
}
