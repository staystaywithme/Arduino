#include <SoftwareSerial.h>

SoftwareSerial mySerial(12,13); // RX, TX，定义使用软件串口，10号为接收端口RX，11号为发送端口TX

void setup() {
  // 打开硬件串行通信，用于输出到串行监视器
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待串行端口打开
  }
  // 打开软件串行通信，用于与WT901BLE通信
  mySerial.begin(115200); // 假设WT901BLE的波特率是115200
}

void loop() { 
  if (mySerial.available() >= 20) { // 如果接收缓冲区中至少有20个字节
    if (mySerial.peek() == 0x55) { // 如果下一个字节是包头（0x55）
      byte buf[20]; // 创建一个数组，用于存储数据包
      mySerial.readBytes(buf, 20); // 读取20个字节的数据包

      // 判断数据帧的头部是否为0x55 0x61，即为合法数据帧
      if(buf[0]==0x55 && buf[1]==0x61) {
        short value[10]; // 存储每一个解析后的数据值
        for(int i=0; i<10; i++) {
          value[i] = buf[i*2+2] | buf[i*2+3]<<8; // 将两个字节的数据合并为一个值
        }

        float acc[3]; // 存储加速度数据
        float gyro[3]; // 存储角速度数据
        float angle[3]; // 存储角度数据

        // 对加速度、角速度、角度数据进行解析
        for(int i=0; i<3; i++) {
          acc[i] = value[i] / 32768.0 * 16;
          gyro[i] = value[i+3] / 32768.0 * 2000;
          angle[i] = value[i+6] / 32768.0 * 180;
        }

      // 打印加速度数据
      //Serial.print(acc[0]);Serial.print(", ");
      //Serial.print(acc[1]);Serial.print(", ");
      //Serial.print(acc[2]);Serial.print(", ");
      // 打印角速度数据
      //Serial.print(gyro[0]);Serial.print(", ");
      //Serial.print(gyro[1]);Serial.print(", ");
      //Serial.print(gyro[2]);Serial.print(", ");
      // 打印角度数据
      Serial.print(angle[0]);Serial.print(",");
      Serial.print(angle[1]);Serial.print(",");
      Serial.println(angle[2]);
      }
    } else {
      mySerial.read(); // 不是包头，舍弃这个字节
    }
  }
}