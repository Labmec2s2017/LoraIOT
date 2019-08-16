//programacion autor : Nelson Castillo
// ------------------EMISOR-------------------------------------------------------
//descripcion codigo : codigo que envia un hello y un contador a un micro receptor,se implementa en STM32f103 CON LORA RA-02
//la antena utilizada es un resorte que puse(mejoro la señal).
//pinout de conexion :   STM32   ------------- RA-02              
//                       GND --------------->  GND
//                       3,3V--------------->  3,3V
//                       PA1 --------------->  DIO0
//                       PA4---------------->  NSS
//                       PA5 --------------->  SCK
//                       PA6 --------------->  MISO
//                       PA7 --------------->  MOSI
//                       PC14 ---------------> RST
//                       PB13 ---------------> DIO1
//                       PB12 ---------------> DIO3
//---------------------------------------------------------------------------------
//PINOUT DE CONEXION :    STM32 --------------FTDI (USB)
//                        GND   -------------> GND
//                        3,3V  -------------> 3,3V   PUEDE SER 5 VOLT EN AMBOS IGUAL
//                        PA9  --------------> RX
//                        PA10 --------------> TX
#include <SPI.h>
#include <LoRa_STM32.h>  //libreria necesaria para la comunicacion

int counter = 0;          // definir contador como un numero entero en valor cero inicial.
const int csPin = PA4;//7;          // LoRa radio chip select
const int resetPin = PC14;//6;       // LoRa radio reset
const int irqPin = PA1;//1;         // change for your board; must be a hardware interrupt pin

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
   // definicion de pines del SPI / override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);      // set CS, reset, IRQ pin
   LoRa.setTxPower(14, PA_OUTPUT_RFO_PIN);    //PA_OUTPUT_PA_BOOST_PIN);
  LoRa.setSignalBandwidth(41.7E3);            //DEFINIR ancho de banda
  LoRa.setSpreadingFactor(12);                //definir spreding factor
  LoRa.setCodingRate4(5);                     // definir coding rate
  
  if (!LoRa.begin(433E6)) {                    //los modulos de 433mhz depende del fabricante
    Serial.println("Starting LoRa failed!");   //mensaje sino es exitisa la comunicacion con lora
    while (1);                  
  }
}

void loop() {
  Serial.print("Sending packet: ");    //MENSAJE X SERIAL DE ENVIO DE DATOS
  Serial.println(counter);             //MUESTRA X SERIAL EL NUMERO CONTADOR

  // ENVIO DE PAQUETES DE DATOS / send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;  //EL CONTADOR SE AUMENTA EN 1 CADA VEZ 

  delay(5000);   // RETARDO DE 5 SEGUNDOS
}
