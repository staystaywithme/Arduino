#include<Wire.h>
#include <MadgwickAHRS.h>
#include <math.h>
Madgwick MadgwickFilter;
  
#define Addr_Accl 0x19  // (JP1,JP2,JP3 = Open)
#define Addr_Gyro 0x69  // (JP1,JP2,JP3 = Open)
#define Addr_Mag 0x13   // (JP1,JP2,JP3 = Open)
#define Addr_Accl2 0x18  // (JP1,JP2,JP3 = shut)
#define Addr_Gyro2 0x68  // (JP1,JP2,JP3 = shut)
#define Addr_Mag2 0x10   // (JP1,JP2,JP3 = shut)

#define GRYO 1
#define ACCL 2
#define MAG 3
#define XYZ_ROTATION 4
float xAccl = 0.00;
float yAccl = 0.00;
float zAccl = 0.00;
float xGyro = 0.00;
float yGyro = 0.00;
float zGyro = 0.00;
float   xMag  = 0;
float   yMag  = 0;
float   zMag  = 0;
float  roll=0  ;
float  pitch=0 ;
float  yaw=0 ;
#define GRYO 5//?
#define ACCL 6
#define MAG 7
#define XYZ_ROTATION 8
float xAccl2 = 0.00;
float yAccl2 = 0.00;
float zAccl2 = 0.00;
float xGyro2 = 0.00;
float yGyro2 = 0.00;
float zGyro2 = 0.00;
float   xMag2  = 0;
float   yMag2  = 0;
float   zMag2  = 0;
float  roll2=0  ;
float  pitch2=0 ;
float  yaw2=0 ;




//=====================================================================================//
void BMX055_Init()
{
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x0F); // Select PMU_Range register
  Wire.write(0x03);   // Range = +/- 2g
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x10);  // Select PMU_BW register
  Wire.write(0x08);  // Bandwidth = 7.81 Hz
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl);
  Wire.write(0x11);  // Select PMU_LPW register
  Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro);
  Wire.write(0x0F);  // Select Range register
  Wire.write(0x04);  // Full scale = +/- 125 degree/s
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro);
  Wire.write(0x10);  // Select Bandwidth register
  Wire.write(0x07);  // ODR = 100 Hz
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro);
  Wire.write(0x11);  // Select LPM1 register
  Wire.write(0x00);  // Normal mode, Sleep duration = 2ms
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x83);  // Soft reset
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x01);  // Soft reset
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x4C);  // Select Mag register
  Wire.write(0x00);  // Normal Mode, ODR = 10 Hz
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x4E);  // Select Mag register
  Wire.write(0x84);  // X, Y, Z-Axis enabled
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x51);  // Select Mag register
  Wire.write(0x04);  // No. of Repetitions for X-Y Axis = 9
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag);
  Wire.write(0x52);  // Select Mag register
  Wire.write(0x16);  // No. of Repetitions for Z-Axis = 15
  Wire.endTransmission();
}
//=====================================================================================//
void BMX055_Accl()
{
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(Addr_Accl);
    Wire.write((2 + i));// Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Accl, 1);// Request 1 byte of data
    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data to 12-bits
  xAccl = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
  if (xAccl > 2047)  xAccl -= 4096;
  yAccl = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
  if (yAccl > 2047)  yAccl -= 4096;
  zAccl = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
  if (zAccl > 2047)  zAccl -= 4096;
  xAccl = xAccl * 0.0098; // renge +-2g
  yAccl = yAccl * 0.0098; // renge +-2g
  zAccl = zAccl * 0.0098; // renge +-2g
}
//=====================================================================================//
void BMX055_Gyro()
{
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(Addr_Gyro);
    Wire.write((2 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Gyro, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  xGyro = (data[1] * 256) + data[0];
  if (xGyro > 32767)  xGyro -= 65536;
  yGyro = (data[3] * 256) + data[2];
  if (yGyro > 32767)  yGyro -= 65536;
  zGyro = (data[5] * 256) + data[4];
  if (zGyro > 32767)  zGyro -= 65536;

  xGyro = xGyro * 0.0038; //  Full scale = +/- 125 degree/s
  yGyro = yGyro * 0.0038; //  Full scale = +/- 125 degree/s
  zGyro = zGyro * 0.0038; //  Full scale = +/- 125 degree/s
}
//=====================================================================================//
void BMX055_Mag()
{
  int data[8];
  for (int i = 0; i < 8; i++)
  {
    Wire.beginTransmission(Addr_Mag);
    Wire.write((0x42 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Mag, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  xMag = ((data[1] <<8) | (data[0]>>3));
  if (xMag > 4095)  xMag -= 8192;
  yMag = ((data[3] <<8) | (data[2]>>3));
  if (yMag > 4095)  yMag -= 8192;
  zMag = ((data[5] <<8) | (data[4]>>3));
  if (zMag > 16383)  zMag -= 32768;
}
void BMX055_Init2()
{
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl2);
  Wire.write(0x0F); // Select PMU_Range register
  Wire.write(0x03);   // Range = +/- 2g
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl2);
  Wire.write(0x10);  // Select PMU_BW register
  Wire.write(0x08);  // Bandwidth = 7.81 Hz
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Accl2);
  Wire.write(0x11);  // Select PMU_LPW register
  Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro2);
  Wire.write(0x0F);  // Select Range register
  Wire.write(0x04);  // Full scale = +/- 125 degree/s
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro2);
  Wire.write(0x10);  // Select Bandwidth register
  Wire.write(0x07);  // ODR = 100 Hz
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Gyro2);
  Wire.write(0x11);  // Select LPM1 register
  Wire.write(0x00);  // Normal mode, Sleep duration = 2ms
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x83);  // Soft reset
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x4B);  // Select Mag register
  Wire.write(0x01);  // Soft reset
  Wire.endTransmission();
  //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x4C);  // Select Mag register
  Wire.write(0x00);  // Normal Mode, ODR = 10 Hz
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x4E);  // Select Mag register
  Wire.write(0x84);  // X, Y, Z-Axis enabled
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x51);  // Select Mag register
  Wire.write(0x04);  // No. of Repetitions for X-Y Axis = 9
  Wire.endTransmission();
 //------------------------------------------------------------//
  Wire.beginTransmission(Addr_Mag2);
  Wire.write(0x52);  // Select Mag register
  Wire.write(0x16);  // No. of Repetitions for Z-Axis = 15
  Wire.endTransmission();
}
//=====================================================================================//
void BMX055_Accl2()
{
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(Addr_Accl2);
    Wire.write((2 + i));// Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Accl2, 1);// Request 1 byte of data
    // Read 6 bytes of data
    // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data to 12-bits
  xAccl2 = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
  if (xAccl2 > 2047)  xAccl2 -= 4096;
  yAccl2 = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
  if (yAccl2 > 2047)  yAccl2 -= 4096;
  zAccl2 = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
  if (zAccl > 2047)  zAccl -= 4096;
  xAccl2 = xAccl2 * 0.0098; // renge +-2g
  yAccl2 = yAccl2 * 0.0098; // renge +-2g
  zAccl2 = zAccl2 * 0.0098; // renge +-2g
}
//=====================================================================================//
void BMX055_Gyro2()
{
  int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(Addr_Gyro2);
    Wire.write((2 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Gyro2, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  xGyro2 = (data[1] * 256) + data[0];
  if (xGyro2 > 32767)  xGyro2 -= 65536;
  yGyro2 = (data[3] * 256) + data[2];
  if (yGyro2 > 32767)  yGyro2 -= 65536;
  zGyro2 = (data[5] * 256) + data[4];
  if (zGyro2 > 32767)  zGyro2 -= 65536;

  xGyro2 = xGyro2 * 0.0038; //  Full scale = +/- 125 degree/s
  yGyro2 = yGyro2 * 0.0038; //  Full scale = +/- 125 degree/s
  zGyro2 = zGyro2 * 0.0038; //  Full scale = +/- 125 degree/s
}
//=====================================================================================//
void BMX055_Mag2()
{
  int data[8];
  for (int i = 0; i < 8; i++)
  {
    Wire.beginTransmission(Addr_Mag2);
    Wire.write((0x42 + i));    // Select data register
    Wire.endTransmission();
    Wire.requestFrom(Addr_Mag2, 1);    // Request 1 byte of data
    // Read 6 bytes of data
    // xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
    if (Wire.available() == 1)
      data[i] = Wire.read();
  }
  // Convert the data
  xMag2 = ((data[1] <<8) | (data[0]>>3));
  if (xMag2 > 4095)  xMag2 -= 8192;
  yMag2 = ((data[3] <<8) | (data[2]>>3));
  if (yMag2 > 4095)  yMag2 -= 8192;
  zMag2 = ((data[5] <<8) | (data[4]>>3));
  if (zMag2 > 16383)  zMag2 -= 32768;
}
void setup()
{
  // Wire(Arduino-I2C)
  Wire.begin();
  // 115200bps
  Serial.begin(115200);
  //BMX055 
  BMX055_Init();
  BMX055_Init2();
  MadgwickFilter.begin(10);
}

void loop()
{
  BMX055_Gyro();
  //Serial.print(GRYO);//gryo==1
  //Serial.print(",");
  Serial.print(xGyro);
  Serial.print(",");
  Serial.print(yGyro);
  Serial.print(",");
  Serial.print(zGyro); 
  Serial.print(",");
 
  BMX055_Accl();
  //Serial.print(ACCL);//accl ==2
  //Serial.print(",");
  Serial.print(xAccl);
  Serial.print(",");
  Serial.print(yAccl);
  Serial.print(",");
  Serial.print(zAccl);
  Serial.print(",");
 
  BMX055_Mag();
  /*Serial.print(MAG);//mag==3
  Serial.print(",");
  Serial.print(xMag);
  Serial.print(",");
  Serial.print(yMag);
  Serial.print(",");
  Serial.print(zMag);
  Serial.print(",");*/
MadgwickFilter.update(xGyro,yGyro,zGyro,xAccl,yAccl,zAccl,xMag,yMag,zMag);
 roll  = MadgwickFilter.getRoll();
 pitch = MadgwickFilter.getPitch();
 yaw   = MadgwickFilter.getYaw();
  Serial.print(XYZ_ROTATION);//XYZ_ROTATION=4
  Serial.print(",");
  Serial.print(roll); 
  Serial.print(",");
  Serial.print(pitch); 
  Serial.print(",");
  Serial.print(yaw);
  Serial.print(",");

 BMX055_Gyro2();
  //Serial.print(GRYO);//gryo==1
  //Serial.print(",");
  Serial.print(xGyro2);
  Serial.print(",");
  Serial.print(yGyro2);
  Serial.print(",");
  Serial.print(zGyro2); 
  Serial.print(",");
 
  BMX055_Accl2();
  //Serial.print(ACCL);//accl ==2
  //Serial.print(",");
  Serial.print(xAccl2);
  Serial.print(",");
  Serial.print(yAccl2);
  Serial.print(",");
  Serial.print(zAccl2);
  Serial.print(",");
 
  BMX055_Mag2();
  /*Serial.print(MAG);//mag==3
  Serial.print(",");
  Serial.print(xMag2);
  Serial.print(",");
  Serial.print(yMag2);
  Serial.print(",");
  Serial.print(zMag2);
  Serial.print(",");*/
MadgwickFilter.update(xGyro2,yGyro2,zGyro2,xAccl2,yAccl2,zAccl2,xMag2,yMag2,zMag2);
 roll2  = MadgwickFilter.getRoll();
 pitch2 = MadgwickFilter.getPitch();
 yaw2   = MadgwickFilter.getYaw();
  Serial.print(XYZ_ROTATION);//XYZ_ROTATION=4
  Serial.print(",");
  Serial.print(roll2); 
  Serial.print(",");
  Serial.print(pitch2); 
  Serial.print(",");
  Serial.println(yaw2);
}