#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10); //CE,CSNのピンをを指定

byte addr[][6] = {"addr0", "addr1"};

void setup() {
  Serial.begin(9800);
  Serial.println(F("start"));
  radio.begin();
  //radio.setAutoAck(false);
  radio.setPALevel( RF24_PA_LOW );
  radio.openWritingPipe(addr[1]);
  radio.openReadingPipe(1, addr[0]);
  radio.startListening();
  Serial.println("Listening started without problem");
}

void loop() {
  char c = 'a';
  radio.stopListening();
  if (!radio.write( &c, sizeof(char) )) {
    Serial.println(F("failed"));
  }
  else if (radio.write( &c, sizeof(char) )) {
    Serial.println("Write success");
  }
  //radio.write( &c, sizeof(char));
  radio.startListening();
  if (radio.available() ) {
    radio.read( &c, sizeof(char) );
    Serial.print(c);
  }

  delay(10);
}