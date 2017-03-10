/***
    eeprom_put example.

    This shows how to use the EEPROM.put() method.
    Also, this sketch will pre-set the EEPROM data for the
    example sketch eeprom_get.

    Note, unlike the single byte version EEPROM.write(),
    the put method will use update semantics. As in a byte
    will only be written to the EEPROM if the data is actually
    different.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

#include <EEPROM.h>
#define MAC_ADDR_SIZE 6

struct PanelId {
  byte mac[MAC_ADDR_SIZE];
};

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  int eeAddress = 0;   //Location we want the data to be put.

  /** Put is designed for use with custom structures also. **/

  //Id to store.
  PanelId panel = {
   { 0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00 }
  };

  EEPROM.put(eeAddress, panel);
  Serial.print("Written ID data");

  PanelId panelReadVal; //Variable to store custom object read from EEPROM.
  EEPROM.get(eeAddress, panelReadVal);

  Serial.println("Read ID from EEPROM: ");
  Serial.println("mac address = ");
  for(int i = 0; i < MAC_ADDR_SIZE; i++){
    if (i){
          Serial.print(':');
    }
    Serial.print(panelReadVal.mac[i],HEX);
  }
  Serial.println("");
  Serial.println("done");
}

void loop() {
  /* Empty loop */
}
