#include "LP50XX.h"
#include <Wire.h>

#define ENABLE_PIN 9
LP50XX device_top(ENABLE_PIN);
LP50XX device_middle(ENABLE_PIN);
LP50XX device_bottom(ENABLE_PIN);

// Use this if you don't have an enable pin
// LP50XX device;

void setup() {
  // put your setup code here, to run once:

  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Wire.begin(14);

  // Support for 400kHz available
  Wire.setClock(400000UL);

  device_middle.Begin(0x15);
  device_top.Begin(0x14);
  device_bottom.Begin(0x16);
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   for (int i = 0; i < 12; i++) {
//     device_bottom.SetOutputColor(i, 255);
//     delay(200);
//     device_bottom.SetOutputColor(i, 0);
//     //delay(200);
//   }

//   for (int i = 0; i < 12; i++) {
//     device_middle.SetOutputColor(i, 255);
//     delay(200);
//     device_middle.SetOutputColor(i, 0);
//     //delay(200);
//   }


//   for (int i = 0; i < 12; i++) {
//     device_top.SetOutputColor(i, 255);
//     delay(200);
//     device_top.SetOutputColor(i, 0);
//     //delay(200);
//   }


//   Serial.println("Hello, World!");
// }

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of the Write.endTransmisstion to determine
    // if a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }

  delay(2000); // Wait 5 seconds for the next scan
}