//system
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
float V_a0,Rs,I,V,x1,x2,COP,F1,F2;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue0=analogRead(A0);//read A0
int sensorValue1=analogRead(A1);//read A１
int sensorValue2=analogRead(A2);//read A2
int sensorValue3=analogRead(A3);//read A3
//V_a0=sensorValue*5.00/1023.00;
//Serial.println(sensorValue0); 
//Serial.println(sensorValue3); 
//Serial.println(sensorValue1); 
//Serial.println(sensorValue2); 

//calculate COP
x1=-100;
x2=100;
if (sensorValue0>500) {
F1=(250*sensorValue3)/12069 - 17660/1341;
F2=(250*sensorValue0)/12069 - 17660/1341;
COP=(F1*x1+F2*x2)/(F1+F2);
}
else {
  COP=0;
}
//Serial.println(F1); 
//Serial.println(F2); 
//Serial.println(COP); 

if (radio.write(&COP, sizeof(COP))) {
  Serial.println("Data sent successfully");
} else {
  Serial.println("Failed to send data");
}
  delay(1000);
}