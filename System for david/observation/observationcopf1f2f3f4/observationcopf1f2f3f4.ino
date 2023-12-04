#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
float receivedData[10]; // Array to hold received values: cop, F1 to F9

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData)); // Read all data

    // Loop through array and print values
    for (int i = 0; i < 10; i++) { // Increase loop count to 10
      Serial.print(receivedData[i]);
      if (i != 9) { // Don't add comma after the last value
        Serial.print(",");
      }
    }
    Serial.println(); // Newline for next set of data
  }
}
