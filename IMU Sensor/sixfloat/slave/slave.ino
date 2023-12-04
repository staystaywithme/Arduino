#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
float receivedData[6]; // Array to hold received values

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData)); // Read all data

    // Loop through array and print values
    for (int i = 0; i < 6; i++) { // Increase loop count to 10
      Serial.print(receivedData[i]);
      if (i != 5) { // Don't add comma after the last value
        Serial.print(",");
      }
    }
    Serial.println(); // Newline for next set of data
  }
}