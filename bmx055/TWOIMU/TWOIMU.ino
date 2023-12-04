#include <Wire.h>
#include <MadgwickAHRS.h>
#include <math.h>

Madgwick MadgwickFilter1;
Madgwick MadgwickFilter2;
#define Addr_Accl1 0x19
#define Addr_Gyro1 0x69
#define Addr_Mag1 0x13
#define Addr_Accl2 0x18
#define Addr_Gyro2 0x68
#define Addr_Mag2 0x10

float xAccl1 = 0.00, yAccl1 = 0.00, zAccl1 = 0.00;
float xGyro1 = 0.00, yGyro1 = 0.00, zGyro1 = 0.00;
float xMag1 = 0, yMag1 = 0, zMag1 = 0;
float roll1 = 0, pitch1 = 0, yaw1 = 0;

float xAccl2 = 0.00, yAccl2 = 0.00, zAccl2 = 0.00;
float xGyro2 = 0.00, yGyro2 = 0.00, zGyro2 = 0.00;
float xMag2 = 0, yMag2 = 0, zMag2 = 0;
float roll2 = 0, pitch2 = 0, yaw2 = 0;

void BMX055_Init(uint8_t Addr_Accl, uint8_t Addr_Gyro, uint8_t Addr_Mag);
void BMX055_Accl(uint8_t Addr_Accl, float &xAccl, float &yAccl, float &zAccl);
void BMX055_Gyro(uint8_t Addr_Gyro, float &xGyro, float &yGyro, float &zGyro);
void BMX055_Mag(uint8_t Addr_Mag, float &xMag, float &yMag, float &zMag);

void setup() {
    Wire.begin();
    Wire.setClock(400000L);  // 设置I2C速度为400kHz
    Serial.begin(115200);
    BMX055_Init(Addr_Accl1, Addr_Gyro1, Addr_Mag1);
    BMX055_Init(Addr_Accl2, Addr_Gyro2, Addr_Mag2);
    MadgwickFilter1.begin(60);
    MadgwickFilter2.begin(60);
}

void loop() {
    BMX055_Gyro(Addr_Gyro1, xGyro1, yGyro1, zGyro1);
    BMX055_Accl(Addr_Accl1, xAccl1, yAccl1, zAccl1);
    BMX055_Mag(Addr_Mag1, xMag1, yMag1, zMag1);

    MadgwickFilter1.update(xGyro1, yGyro1, zGyro1, xAccl1, yAccl1, zAccl1, xMag1, yMag1, zMag1);
    roll1 = MadgwickFilter1.getRoll();
    pitch1 = MadgwickFilter1.getPitch();
    yaw1 = MadgwickFilter1.getYaw();

    Serial.print(xGyro1); Serial.print(",");
    Serial.print(yGyro1); Serial.print(",");
    Serial.print(zGyro1); Serial.print(",");
    Serial.print(xAccl1); Serial.print(",");
    Serial.print(yAccl1); Serial.print(",");
    Serial.print(zAccl1); Serial.print(",");
    Serial.print(roll1); Serial.print(",");
    Serial.print(pitch1); Serial.print(",");
    Serial.print(yaw1); Serial.print(",");

    BMX055_Gyro(Addr_Gyro2, xGyro2, yGyro2, zGyro2);
    BMX055_Accl(Addr_Accl2, xAccl2, yAccl2, zAccl2);
    BMX055_Mag(Addr_Mag2, xMag2, yMag2, zMag2);

    MadgwickFilter2.update(xGyro2, yGyro2, zGyro2, xAccl2, yAccl2, zAccl2, xMag2, yMag2, zMag2);
    roll2 = MadgwickFilter2.getRoll();
    pitch2 = MadgwickFilter2.getPitch();
    yaw2 = MadgwickFilter2.getYaw();

    Serial.print(xGyro2); Serial.print(",");
    Serial.print(yGyro2); Serial.print(",");
    Serial.print(zGyro2); Serial.print(",");
    Serial.print(xAccl2); Serial.print(",");
    Serial.print(yAccl2); Serial.print(",");
    Serial.print(zAccl2); Serial.print(",");
    Serial.print(roll2); Serial.print(",");
    Serial.print(pitch2); Serial.print(",");
    Serial.println(yaw2);
}

void BMX055_Init(uint8_t Addr_Accl, uint8_t Addr_Gyro, uint8_t Addr_Mag) {
    // Initialization for Accelerometer
    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x0F); // Select PMU_Range register
    Wire.write(0x03); // Range = +/- 2g
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x10); // Select PMU_BW register
    Wire.write(0x08); // Bandwidth = 7.81 Hz
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Accl);
    Wire.write(0x11); // Select PMU_LPW register
    Wire.write(0x00); // Normal mode, Sleep duration = 0.5ms
    Wire.endTransmission();

    // Initialization for Gyroscope
    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x0F); // Select Range register
    Wire.write(0x04); // Full scale = +/- 125 degree/s
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x10); // Select Bandwidth register
    Wire.write(0x07); // ODR = 100 Hz
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Gyro);
    Wire.write(0x11); // Select LPM1 register
    Wire.write(0x00); // Normal mode, Sleep duration = 2ms
    Wire.endTransmission();

    // Initialization for Magnetometer
    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4B); // Select Mag register
    Wire.write(0x83); // Soft reset
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4B); // Select Mag register
    Wire.write(0x01); // Soft reset
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4C); // Select Mag register
    Wire.write(0x00); // Normal Mode, ODR = 10 Hz
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x4E); // Select Mag register
    Wire.write(0x84); // X, Y, Z-Axis enabled
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x51); // Select Mag register
    Wire.write(0x04); // No. of Repetitions for X-Y Axis = 9
    Wire.endTransmission();

    Wire.beginTransmission(Addr_Mag);
    Wire.write(0x52); // Select Mag register
    Wire.write(0x16); // No. of Repetitions for Z-Axis = 15
    Wire.endTransmission();
}

void BMX055_Accl(uint8_t Addr_Accl, float &xAccl, float &yAccl, float &zAccl) {
    int data[6];
    for (int i = 0; i < 6; i++) {
        Wire.beginTransmission(Addr_Accl);
        Wire.write((2 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Accl, 1); // Request 1 byte of data
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data to 12-bits
    xAccl = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
    if (xAccl > 2047) xAccl -= 4096;
    yAccl = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
    if (yAccl > 2047) yAccl -= 4096;
    zAccl = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
    if (zAccl > 2047) zAccl -= 4096;
    xAccl = xAccl * 0.0098; // range +-2g
    yAccl = yAccl * 0.0098; // range +-2g
    zAccl = zAccl * 0.0098; // range +-2g
}

void BMX055_Gyro(uint8_t Addr_Gyro, float &xGyro, float &yGyro, float &zGyro) {
    int data[6];
    for (int i = 0; i < 6; i++) {
        Wire.beginTransmission(Addr_Gyro);
        Wire.write((2 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Gyro, 1); // Request 1 byte of data
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data
    xGyro = (data[1] * 256) + data[0];
    if (xGyro > 32767) xGyro -= 65536;
    yGyro = (data[3] * 256) + data[2];
    if (yGyro > 32767) yGyro -= 65536;
    zGyro = (data[5] * 256) + data[4];
    if (zGyro > 32767) zGyro -= 65536;
    xGyro = xGyro * 0.0038; // Full scale = +/- 125 degree/s
    yGyro = yGyro * 0.0038; // Full scale = +/- 125 degree/s
    zGyro = zGyro * 0.0038; // Full scale = +/- 125 degree/s
}

void BMX055_Mag(uint8_t Addr_Mag, float &xMag, float &yMag, float &zMag) {
    int data[8];
    for (int i = 0; i < 8; i++) {
        Wire.beginTransmission(Addr_Mag);
        Wire.write((0x42 + i)); // Select data register
        Wire.endTransmission();
        Wire.requestFrom(Addr_Mag, 1); // Request 1 byte of data
        if (Wire.available() == 1)
            data[i] = Wire.read();
    }
    // Convert the data
    xMag = ((data[1] << 8) | (data[0] >> 3));
    if (xMag > 4095) xMag -= 8192;
    yMag = ((data[3] << 8) | (data[2] >> 3));
    if (yMag > 4095) yMag -= 8192;
    zMag = ((data[5] << 8) | (data[4] >> 3));
    if (zMag > 16383) zMag -= 32768;
}

