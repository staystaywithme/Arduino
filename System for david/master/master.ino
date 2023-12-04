//system
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
float x1,x2,x3,x4,COP,F0,F1,F2,F3,F4;
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
int sensorValue4=analogRead(A4);//read A4
//V_a0=sensorValue*5.00/1023.00;

//calculate COP
x1=-10;
x2=-5;
x3=5;
x4=10;

if (sensorValue0<100 ) {
if (sensorValue1>500 ) {
F1=9*sensorValue1 - 5940;
}
else {
  F1=0;
}
 if (sensorValue2>500) {
   F2=9*sensorValue2 - 5940;
 }
else {
  F2=0;
}
if (sensorValue3>500 ) {
F3=9*sensorValue3 - 5940;
}
else {
  F3=0;
}
if (sensorValue4>500 ) {
F4=9*sensorValue4 - 5940;
}
else {
  F4=0;
}
COP=(F1*x1+F2*x2+F3*x3+F4*x4);
}
else {
  COP=0;
}
//Serial.println(sensorValue0); 
//Serial.println(sensorValue1); 
//Serial.println(sensorValue2); 
//Serial.println(sensorValue3); 
//Serial.println(sensorValue4); 
Serial.println(F1); 
Serial.println(F2); 
Serial.println(F3); 
Serial.println(F4); 
Serial.println(COP); 

//send COP
if (radio.write(&COP, sizeof(COP))) {
  Serial.println("Data sent successfully");
} else {
  Serial.println("Failed to send data");
}
  delay(100);
}