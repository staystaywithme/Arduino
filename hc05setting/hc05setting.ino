// Bluetoothモジュール HC-05(HC-06) ATモード設定用スケッチ
// シリアルモニタを使用した通信スケッチになります
// https://burariweb.info
//
// HC-05はスイッチを押しながら電源投入でATモードに入ります。
// HC-06は電源投入と同時にATモードに入ります。
//
// デフォルトのボーレートは HC-05（34800bps)・HC-06(9600bps)となっています。
// HC-05は［NL+CR］、HC-06は［改行なし］でコマンドを送信！
//

#include <SoftwareSerial.h>
// Bluetoothモジュールとはソフトウェアシリアルで通信。
// TXD-(Arduino)D2,RXD-(Arduino)D3に接続。
// ArduinoからのTXは分圧してBluetoothモジュールのRXDに接続。

  SoftwareSerial BTserial(2, 3);  // RX,TX


void setup() 
{
    Serial.begin(9600);
    Serial.println("AT コマンドを入力 :");
    
// HC-05のデフォルトでのボーレートは38400
// HC-06のデフォルトのボーレートは9600
    BTserial.begin(38400);
}

void loop()
{
// HC-05(HC-06)から読み取りシリアルモニタに送信する
    if (BTserial.available())
    {  
        Serial.write(BTserial.read());
        
    }
 
// シリアルモニタからのデータを読み取りHC-05(HC-06)に送信する
    if (Serial.available())
    {
        BTserial.write(Serial.read());
    }
}