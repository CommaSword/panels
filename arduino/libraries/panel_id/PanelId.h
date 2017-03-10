#ifndef PanelId_h
#define PanelId_h

#include "EEPROM.h"

#define MAC_ADDR_SIZE 6
#define EE_ADDRESS 0
#define BYTE unsigned char

struct PanelId {
  BYTE mac[MAC_ADDR_SIZE];
};

class PanelIdManager{
public:
    PanelId read();
    void write(PanelId id);
    void print(PanelId id);
};

#endif