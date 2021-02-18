/*************************************************************
  This is an examples for the RL01-02-03 Radio Range

  You can buy one on our store!
  -----> https://xinabox.cc/products/RL01/
  -----> https://xinabox.cc/products/RL02/
  -----> https://xinabox.cc/products/RL03/

  This example requests the Alcohol sensor to measure
  the Breath Alcohol Level

  Currently Supported on the following ☒CHIPs:
  - CW01
  - CR01/02/03

  The sensor communicates over the I2C Bus.

  ------------------------TIPS--------------------------
  Change this line ----->Wire.begin(2,14);
  to this      ----->Wire.begin();
  to allow this sensor to communicate other cpus

*************************************************************/

#include <xCore.h>
#include <xRL0x.h>
#include <xOD01.h>

#define RL03_FREQ 915.0

#define CW01_RED 12
#define CW01_GREEN 13
#define CW01_BLUE 5

int i;
String mode;

xOD01 OD01;

const int DELAY_TIME = 1500;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Set the RGB Pin directions
  pinMode(CW01_RED, OUTPUT);
  pinMode(CW01_GREEN, OUTPUT);
  pinMode(CW01_BLUE, OUTPUT);

  // Start the I2C Comunication
  Wire.pins(2, 14);
  Wire.begin();
  Wire.setClockStretchLimit(15000);

  OD01.begin();
  delay(DELAY_TIME);

  if (!RL0X.begin()) { // <-- enter radio name here
    OD01.println("Check the connector to RL03");
    while (1) {
      // Flash RED to indicate failure
      digitalWrite(CW01_RED, HIGH);
      delay(100);
      digitalWrite(CW01_RED, LOW);
      delay(100);
    }
  } else {
    // RL0X Initialized correctly
    mode = "Bw31_25Cr48Sf512";
    RL0X.setModemConfig(RL0X.Bw31_25Cr48Sf512);
    i = 0;
    
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
  }
  OD01.println("setup done");
}

void loop() {
  if (i % 40 < 10){
    mode = "Bw31_25Cr48Sf512";
    RL0X.setModemConfig(RL0X.Bw31_25Cr48Sf512);
  } else if (i % 40 < 20){
    mode = "Bw125Cr45Sf128";
    RL0X.setModemConfig(RL0X.Bw125Cr45Sf128);
  } else if (i % 40 < 30){
    mode = "Bw500Cr45Sf128";
    RL0X.setModemConfig(RL0X.Bw500Cr45Sf128);
  } else{
    mode = "Bw125Cr48Sf4096";
    RL0X.setModemConfig(RL0X.Bw125Cr48Sf4096);
  }
  
  digitalWrite(CW01_BLUE,HIGH);
  OD01.println("Waiting");
  if (RL0X.waitAvailableTimeout(3000)) {
    uint8_t buf[195];
    uint8_t len = sizeof(buf);
    if (RL0X.recv(buf, &len)) {
      digitalWrite(CW01_RED, HIGH);
      OD01.println("got message: ");
      OD01.println((char*)buf);
      OD01.print("RSSI: ");
      OD01.println(RL0X.lastRssi(), DEC);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      delay(100);
      RL0X.send(data, sizeof(data));
      OD01.println("Sent a reply");
      digitalWrite(CW01_RED, LOW);

      i += 1;
    } else {
      OD01.println("recv failed");
    }
  }
  digitalWrite(CW01_BLUE,LOW);
}
