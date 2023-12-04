//by using Op Amp Circuit
float V_a0;
const int led_pin=13;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(led_pin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue=analogRead(A0);
V_a0=sensorValue*5.00/1023.00;
Serial.println(sensorValue);

if (sensorValue>350)//filter noise
{
  digitalWrite(led_pin,HIGH);
}
else{
  digitalWrite(led_pin,LOW);
}
delay(100);
}
