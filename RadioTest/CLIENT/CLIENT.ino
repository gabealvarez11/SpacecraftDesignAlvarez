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
*************************************************************/

#include <xCore.h>
#include <xRL0x.h>

#define RL03_FREQ 915.0
#define Serial SerialUSB

String mode;
int i;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  while(!Serial);
  // Set the RGB Pin directions
  //pinMode(LED_RED, OUTPUT);
  //pinMode(LED_GREEN, OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);

  // Start the I2C Comunication
  #ifdef ESP8266
    Wire.pins(2, 14);
    Wire.setClockStretchLimit(15000);
  #endif
  Wire.begin();

  if (!RL0X.begin()) {
    Serial.println("Check the connector to CR01");
    while (1) {
      // Flash RED to indicate failure
      digitalWrite(LED_RED, HIGH);
      delay(100);
      digitalWrite(LED_RED, LOW);
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
  Serial.println("Sending to RL0X Server Using " + mode);

  digitalWrite(LED_GREEN, HIGH);

  uint8_t data[] = "Hello World!";
  delay(100);
  RL0X.send(data, sizeof(data));

  uint8_t buf[195];
  uint8_t len = sizeof(buf);

  if (RL0X.waitAvailableTimeout(3000)) {
    if (RL0X.recv(buf, &len)) {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(RL0X.lastRssi(), DEC);
      i += 1;
    } else {
      Serial.println("recv failed");
    }
  } else {
    digitalWrite(LED_GREEN, LOW);
    Serial.println("No reply, is the RL01 server running ?");
  }
}
