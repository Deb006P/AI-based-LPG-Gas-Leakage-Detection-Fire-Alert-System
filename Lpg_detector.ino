#include<Servo.h>
Servo s1;
void setup() {
  // put your setup code here, to run once:
s1.attach(7);//servo
s1.write(0);
pinMode(5,OUTPUT);//buzzer
pinMode(2,INPUT);//gas sensor
pinMode(9,OUTPUT);//relay 
pinMode(6,OUTPUT);//EXHOST
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(2)==LOW){
  digitalWrite(5,HIGH);
    digitalWrite(9,LOW);
  digitalWrite(6,HIGH);
s1.write(180);
  
   Serial.println("Gas detected! Danger!");

}
  else{
    digitalWrite(5,LOW);
      digitalWrite(9,HIGH);
       digitalWrite(6,LOW);
      s1.write(0);
       Serial.println("No gas detected. Safe.");


}
 delay(1000);
}