//system
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

struct SensorData {
  float COP;
  float F1;
  float F2;
  float F3;
  float F4;
  float F5;
  float F6;
  float F7;
  float F8;
  float F9;
  float F10;
};

SensorData dataToSend;

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
  int sensorValue1=analogRead(A1);//read A1
  int sensorValue2=analogRead(A2);//read A2
  int sensorValue3=analogRead(A3);//read A3
  int sensorValue4=analogRead(A4);//read A4
  int sensorValue5=analogRead(A5);//read A5
  int sensorValue6=analogRead(A6);//read A6
  int sensorValue7=analogRead(A7);//read A7
  int sensorValue8=analogRead(A8);//read A8
  int sensorValue9=analogRead(A9);//read A9

  //calculate COP
  float x1=-10;
  float x2=-5;
  float x3=5;
  float x4=10;
  float F0, F1, F2, F3, F4,F5,F6,F7,F8,F9, COP;

  if (sensorValue0<500 ) {
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
     if (sensorValue5>500 ) {
      F5=9*sensorValue5 - 5940;
    }
    else {
      F5=0;
    }
     if (sensorValue6>500 ) {
      F6=9*sensorValue6 - 5940;
    }
    else {
      F6=0;
    }
     if (sensorValue7>500 ) {
      F7=9*sensorValue7 - 5940;
    }
    else {
      F7=0;
    }
     if (sensorValue8>500 ) {
      F8=9*sensorValue8 - 5940;
    }
    else {
      F8=0;
    }
     if (sensorValue9>500 ) {
      F9=9*sensorValue9 - 5940;
    }
    else {
      F9=0;
    }
    COP=(F1*x1+F2*x2+F3*x3+F4*x4);
  }
  else {
    COP=0;
  }
  
  dataToSend.COP = COP;
  dataToSend.F1 = F1;
  dataToSend.F2 = F2;
  dataToSend.F3 = F3;
  dataToSend.F4 = F4;
  dataToSend.F5 = F5;
  dataToSend.F6 = F6;
  dataToSend.F7 = F7;
  dataToSend.F8 = F8;
  dataToSend.F9 = F9;
  
  if (radio.write(&dataToSend, sizeof(dataToSend))) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data");
  }
  delay(10);
}
