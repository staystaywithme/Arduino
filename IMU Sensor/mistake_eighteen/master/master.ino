#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const uint64_t address = 0xE8E8F0F0E1LL; // 设定RF24通信地址

struct SensorData {
  uint8_t dataType;
  float acc1[3];
  float gyro1[3];
  float angle1[3];
  float acc2[3];
  float gyro2[3];
  float angle2[3];
};

SensorData dataToSend;

void setup() {
  // 打开硬件串行通信，用于输出到串行监视器
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待串行端口打开
  }
  // 打开硬件串行通信，用于与WT901BLE通信
  Serial1.begin(115200); // 假设WT901BLE的波特率是115200
  Serial2.begin(115200); // 假设第二个设备的波特率是115200

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
   // 读取串口14, 15的数据
  if (Serial1.available() >= 20) { // 如果接收缓冲区中至少有20个字节
    if (Serial1.peek() == 0x55) { // 如果下一个字节是包头（0x55）
      byte buf[20]; // 创建一个数组，用于存储数据包
      Serial1.readBytes(buf, 20); // 读取20个字节的数据包

      // 判断数据帧的头部是否为0x55 0x61，即为合法数据帧
      if(buf[0]==0x55 && buf[1]==0x61) {
        short value[10]; // 存储每一个解析后的数据值
        for(int i=0; i<10; i++) {
          value[i] =  buf[i*2+3]<<8|buf[i*2+2]; // 将两个字节的数据合并为一个值
        }

        float acc1[3]; // 存储加速度数据
        float gyro1[3]; // 存储角速度数据
        float angle1[3]; // 存储角度数据

        // 对加速度、角速度、角度数据进行解析
        for(int i=0; i<3; i++) {
          acc1[i] = value[i] / 32768.0 * 16;
          gyro1[i] = value[i+3] / 32768.0 * 2000;
          angle1[i] = value[i+6] / 32768.0 * 180;
        }
       // 打印加速度数据
       //Serial.print(acc1[0]);Serial.print(", ");
       //Serial.print(acc1[1]);Serial.print(", ");
       //Serial.print(acc1[2]);Serial.print(", ");
       // 打印角速度数据
       //Serial.print(gyro1[0]);Serial.print(", ");
       //Serial.print(gyro1[1]);Serial.print(", ");
       //Serial.print(gyro1[2]);Serial.print(", ");
        // 打印角度数据
        //Serial.print(angle1[0]);Serial.print(",");
        //Serial.print(angle1[1]);Serial.print(",");
        //Serial.print(angle1[2]);Serial.print(",");
    for(int i=0; i<3; i++) {
    dataToSend.acc1[i] = value[i] / 32768.0 * 16;
    dataToSend.gyro1[i] = value[i+3] / 32768.0 * 2000;
    dataToSend.angle1[i] = value[i+6] / 32768.0 * 180;
  }
      }
    } else {
      Serial1.read(); // 不是包头，舍弃这个字节
    }
  
  }

  // 读取串口16, 17的数据
  if (Serial2.available() >= 20) { // 如果接收缓冲区中至少有20个字节
    if (Serial2.peek() == 0x55) { // 如果下一个字节是包头（0x55）
      byte buf[20]; // 创建一个数组，用于存储数据包
      Serial2.readBytes(buf, 20); // 读取20个字节的数据包

      // 判断数据帧的头部是否为0x55 0x61，即为合法数据帧
      if(buf[0]==0x55 && buf[1]==0x61) {
        short value[10]; // 存储每一个解析后的数据值
        for(int i=0; i<10; i++) {
          value[i] = buf[i*2+2] | buf[i*2+3]<<8; // 将两个字节的数据合并为一个值
        }

        float acc2[3]; // 存储加速度数据
        float gyro2[3]; // 存储角速度数据
        float angle2[3]; // 存储角度数据

        // 对加速度、角速度、角度数据进行解析
        for(int i=0; i<3; i++) {
          acc2[i] = value[i] / 32768.0 * 16;
          gyro2[i] = value[i+3] / 32768.0 * 2000;
          angle2[i] = value[i+6] / 32768.0 * 180;
        }
       // 打印加速度数据
       //Serial.print(acc2[0]);Serial.print(", ");
       //Serial.print(acc2[1]);Serial.print(", ");
       //Serial.print(acc2[2]);Serial.print(", ");
       // 打印角速度数据
       //Serial.print(gyro2[0]);Serial.print(", ");
       //Serial.print(gyro2[1]);Serial.print(", ");
       //Serial.print(gyro2[2]);Serial.print(", ");
        // 打印角度数据
        //Serial.print(angle2[0]);Serial.print(",");
        //Serial.print(angle2[1]);Serial.print(",");
        //Serial.println(angle2[2]); 
        // 对加速度、角速度、角度数据进行解析
  for(int i=0; i<3; i++) {
    dataToSend.acc2[i] = value[i] / 32768.0 * 16;
    dataToSend.gyro2[i] = value[i+3] / 32768.0 * 2000;
    dataToSend.angle2[i] = value[i+6] / 32768.0 * 180;
  }
      }
    } else {
      Serial2.read(); // 不是包头，舍弃这个字节
    }
  
  }

  // 第一次传输
  dataToSend.dataType=1;
  /*dataToSend.acc1[0] = acc1[0];
  dataToSend.acc1[1] = acc1[1];
  dataToSend.acc1[2] = acc1[2];
  dataToSend.gyro1[0] = gyro1[0];
  dataToSend.gyro1[1] = gyro1[1];
  dataToSend.gyro1[2] = gyro1[2];*/
radio.write(&dataToSend, sizeof(dataToSend));

  // 第二次传输
  dataToSend.dataType=2;
  /*dataToSend.angle1[0] = angle1[0];
  dataToSend.angle1[1] = angle1[1];
  dataToSend.angle1[2] = angle1[2];
  dataToSend.acc2[0] = acc2[0];
  dataToSend.acc2[1] = acc2[1];
  dataToSend.acc2[2] = acc2[2];*/
 radio.write(&dataToSend, sizeof(dataToSend));

  // 第三次传输
  dataToSend.dataType=3;
  /*dataToSend.gyro2[0] = gyro2[0];
  dataToSend.gyro2[1] = gyro2[1];
  dataToSend.gyro2[2] = gyro2[2];
  dataToSend.angle2[0] = angle2[0];
  dataToSend.angle2[1] = angle2[1];
  dataToSend.angle2[2] = angle2[2];*/
  radio.write(&dataToSend, sizeof(dataToSend));
  delay(16);
}