
#include <PanelId.h>

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Id to store.
  PanelId panel = {
   { 0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00 }
  };

  PanelIdManager manager = PanelIdManager();
  manager.write(panel);
  Serial.print("Written ID data");

  PanelId panelReadVal = manager.read();

  Serial.println("Read ID from EEPROM: ");
  manager.print(panelReadVal);
  Serial.println("done");
}

void loop() {
  /* Empty loop */
}