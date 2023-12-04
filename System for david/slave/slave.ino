#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  pinMode(13,OUTPUT);
}

void loop() {
  if (radio.available()) {
    float COP;
    radio.read(&COP, sizeof(COP));
    Serial.println(COP);
if(COP>10) {
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  if(COP<-10) {
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  }
  else
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  delay(500);
 }
  }
}