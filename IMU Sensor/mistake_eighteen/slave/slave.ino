#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

struct SensorData {
  uint8_t dataType;
  float acc1[3];
  float gyro1[3];
  float angle1[3];
  float acc2[3];
  float gyro2[3];
  float angle2[3];
};

const uint64_t address = 0xE8E8F0F0E1LL; // 设定RF24通信地址

SensorData dataReceived;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待串行端口打开
  }
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&dataReceived, sizeof(dataReceived));

    // 根据数据类型标识判断接收到的数据类型
    if (dataReceived.dataType == 1) {
      // 第一组数据
      Serial.print("Data Type 1: ");
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.acc1[i]); Serial.print(", ");
      }
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.gyro1[i]); Serial.print(", ");
      }
      Serial.println();
    } else if (dataReceived.dataType == 2) {
      // 第二组数据
      Serial.print("Data Type 2: ");
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.angle1[i]); Serial.print(", ");
      }
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.acc2[i]); Serial.print(", ");
      }
      Serial.println();
    } else if (dataReceived.dataType == 3) {
      // 第三组数据
      Serial.print("Data Type 3: ");
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.gyro2[i]); Serial.print(", ");
      }
      for (int i = 0; i < 3; ++i) {
        Serial.print(dataReceived.angle2[i]); Serial.print(", ");
      }
      Serial.println();
    } else {
      // 未知数据类型
      Serial.println("Unknown Data Type!");
    }
  }
}
/*void loop() {
  if (radio.available()) {
    // 接收第一次传输的数据
    radio.read(&dataReceived, 8 * sizeof(float));
      for (int i = 0; i < 8; ++i) {
      Serial.print(((float*) &dataReceived)[i]); Serial.print(", ");
    }
    // 接收第二次传输的数据
    radio.read(((uint8_t*) &dataReceived) + (8 * sizeof(float)), 8 * sizeof(float));
      for (int i = 8; i < 16; ++i) {
      Serial.print(((float*) &dataReceived)[i]); Serial.print(", ");
    }
    // 接收第三次传输的数据
    radio.read(((uint8_t*) &dataReceived) + (16 * sizeof(float)), 2 * sizeof(float));
      for (int i = 16;i < 17; ++i ){
       Serial.print(((float*) &dataReceived)[i]); Serial.print(", ");
       } 
       Serial.println(((float*) &dataReceived)[17]);
       }
        } 
*/
    // 打印收到的数据
       //Serial.print(dataReceived.acc1[0]);Serial.print(", ");
       //Serial.print(dataReceived.acc1[1]);Serial.print(", ");
       //Serial.print(dataReceived.acc1[2]);Serial.print(", ");
       //Serial.print(dataReceived.gyro1[0]);Serial.print(", ");
       //Serial.print(dataReceived.gyro1[1]);Serial.print(", ");
       //Serial.print(dataReceived.gyro1[2]);Serial.print(", ");
       //Serial.print(dataReceived.angle1[0]);Serial.print(",");
       //Serial.print(dataReceived.angle1[1]);Serial.print(",");
       //Serial.print(dataReceived.angle1[2]);Serial.print(",");
       //Serial.print(dataReceived.acc2[0]);Serial.print(", ");
       //Serial.print(dataReceived.acc2[1]);Serial.print(", ");
       //Serial.print(dataReceived.acc2[2]);Serial.print(", ");
       //Serial.print(dataReceived.gyro2[0]);Serial.print(", ");
       //Serial.print(dataReceived.gyro2[1]);Serial.print(", ");
       //Serial.print(dataReceived.gyro2[2]);Serial.print(", ");
       //Serial.print(dataReceived.angle2[0]);Serial.print(",");
       //Serial.print(dataReceived.angle2[1]);Serial.print(",");
       //Serial.println(dataReceived.angle2[2]); 