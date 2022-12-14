/* 
 * File:    BLE_Test.ino
 * Author:  Agent Hitman Faris
 * Date:    14 December 2022
 *
 * Description:
 *          Arduino Testing for Bluetooth connection
 * 
 * Revision:
 *          v0  Initial Release For BLE Testing
 *          
 */
 
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int ledPin =  25;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); //Bluetooth device name
  Serial.println("Bluetooth started");
  pinMode(ledPin, OUTPUT);

}

String message = "";
char incomingChar;

void loop() {
  // Read Custum massage
  if (SerialBT.available())
  {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
      message += String(incomingChar);
    }
    else
    {
      message = "";
    }
    Serial.write(incomingChar);
  }
  // Check received message 
  if (message =="on")
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("");
    Serial.println("Door open!");
  }
  else if (message =="off")
  {
    digitalWrite(ledPin, LOW);
    Serial.println("");
    Serial.println("Door are closing!");
  }
  delay(20);
}
