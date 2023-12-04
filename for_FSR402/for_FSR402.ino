//for Force Sensor FSR402
#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);//set lcd display
const int led_pin=13;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led_pin,OUTPUT);
lcd.begin(16,2);//两行六列
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue=analogRead(A0);//read A0
Serial.println(sensorValue);//print out the value
delay(1);//delay between reads for stability
if (sensorValue>500)
{
  digitalWrite(led_pin,HIGH);
}
else{
  digitalWrite(led_pin,LOW);
}
lcd.setCursor(0,1);//在第二行
lcd.print(sensorValue);//print out sensor value
lcd.clear();//clear display
}