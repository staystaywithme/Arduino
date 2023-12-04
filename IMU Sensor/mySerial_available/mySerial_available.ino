#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

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
      byte data[20]; // 创建一个数组，用于存储数据包
      mySerial.readBytes(data, 20); // 读取20个字节的数据包

      // 你现在可以处理数据包了
      // 这里我们只是将数据包输出到串行监视器
      Serial.print("Received: ");
      for (int i = 0; i < 20; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    } else {
      mySerial.read(); // 不是包头，舍弃这个字节
    }
  }
}
