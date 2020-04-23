void setup() {
  // put your setup code here, to run once:
 pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
     pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int A [] = { 3, 5, 6, 9, 10, 11};
  
  for(int j=0; j<6; j++)
  {
for(int i=0; i<100; i=i+2)  
{
analogWrite( A[j], i);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
for(int i=100; i>0; i=i-2)  //Short Dashes for S
{
analogWrite( A[j], i);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
  }

  for(int j=4; j>0; j--)
  {
for(int i=0; i<100; i=i+2)  //Short Dashes for S
{
analogWrite( A[j], i);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
for(int i=100; i>0; i=i-2)  //Short Dashes for S
{
analogWrite( A[j], i);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
  }
}
