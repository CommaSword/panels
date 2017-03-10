#include "EEPROM.h"
#include "PanelId.h"
#include "Arduino.h"

PanelId PanelIdManager::read(){
  PanelId data;
  EEPROM.get(EE_ADDRESS, data);
  return data;
}

void PanelIdManager::write(PanelId data){
  EEPROM.put(EE_ADDRESS, data);
}

void PanelIdManager::print(PanelId data){
char buffer[17];
    sprintf(buffer, "%.2hhX:%.2hhX:%.2hhX:%.2hhX:%.2hhX:%.2X"
    , data.mac[0], data.mac[1], data.mac[2], data.mac[3], data.mac[4], data.mac[5]);

 Serial.print("mac address = ");
 Serial.println(buffer);
 }