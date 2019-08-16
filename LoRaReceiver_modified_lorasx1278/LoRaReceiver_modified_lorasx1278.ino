#include <SPI.h>
#include <LoRa_STM32.h>

const int csPin = PA4;//7;          // LoRa radio chip select
const int resetPin = PC14;//6;       // LoRa radio reset
const int irqPin = PA1;//1;         // change for your board; must be a hardware interrupt pin

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");
  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin
  LoRa.setTxPower(14, PA_OUTPUT_RFO_PIN);//(17,PA_OUTPUT_PA_BOOST_PIN);
  LoRa.setSignalBandwidth(41.7E3); 
  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(5);
  
  if (!LoRa.begin(433E6)) {
    Serial.println("Stating LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
