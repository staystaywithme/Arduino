#include <SoftwareSerial.h>

SoftwareSerial hc05Serial1(1, 0); // TX,RX
SoftwareSerial hc05Serial2(14, 15); // TX,RX

void setup() {
  Serial.begin(115200); // 用于输出到串行监视器

  hc05Serial1.begin(9600); // 设置第一个HC-05模块的波特率
  hc05Serial2.begin(9600); // 设置第二个HC-05模块的波特率
}

void loop() {
  // 读取第一个WT901BLE模块的数据
  if (hc05Serial1.available() >= 20) { // 如果接收缓冲区中至少有20个字节
    if (hc05Serial1.peek() == 0x55) { // 如果下一个字节是包头（0x55）
      byte buf[20]; // 创建一个数组，用于存储数据包
      hc05Serial1.readBytes(buf, 20); // 读取20个字节的数据包

      // 判断数据帧的头部是否为0x55 0x61，即为合法数据帧
      if(buf[0]==0x55 && buf[1]==0x61) {
        short value[10]; // 存储每一个解析后的数据值
        for(int i=0; i<10; i++) {
          value[i] = buf[i*2+2] | buf[i*2+3]<<8; // 将两个字节的数据合并为一个值
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
       Serial.print(acc1[0]);Serial.print(", ");
       Serial.print(acc1[1]);Serial.print(", ");
       Serial.print(acc1[2]);Serial.print(", ");
       // 打印角速度数据
       Serial.print(gyro1[0]);Serial.print(", ");
       Serial.print(gyro1[1]);Serial.print(", ");
       Serial.print(gyro1[2]);Serial.print(", ");
        // 打印角度数据
        Serial.print(angle1[0]);
        Serial.print(",");
        Serial.print(angle1[1]);
        Serial.print(",");
        Serial.print(angle1[2]);
        Serial.print(",");
      }
    } else {
      hc05Serial1.read(); // 不是包头，舍弃这个字节
    }
  
  }

  // 读取第二个WT901BLE模块的数据
if (hc05Serial2.available() >= 20) { // 如果接收缓冲区中至少有20个字节
    if (hc05Serial2.peek() == 0x55) { // 如果下一个字节是包头（0x55）
      byte buf[20]; // 创建一个数组，用于存储数据包
      hc05Serial2.readBytes(buf, 20); // 读取20个字节的数据包

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
       Serial.print(acc2[0]);Serial.print(", ");
       Serial.print(acc2[1]);Serial.print(", ");
       Serial.print(acc2[2]);Serial.print(", ");
       // 打印角速度数据
       Serial.print(gyro2[0]);Serial.print(", ");
       Serial.print(gyro2[1]);Serial.print(", ");
       Serial.print(gyro2[2]);Serial.print(", ");
        // 打印角度数据
        Serial.print(angle2[0]);
        Serial.print(",");
        Serial.print(angle2[1]);
        Serial.print(",");
        Serial.println(angle2[2]);
      }
    } else {
      hc05Serial1.read(); // 不是包头，舍弃这个字节
    }
  
  }
}
