
#include <UIPEthernet.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

EthernetUDP udp;

void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(192,168,1,102));

  int success = udp.begin(5000);

  Serial.print("initialize: ");
  Serial.println(success ? "success" : "failed");

}


void led(OSCMessage &msg) {
  Serial.println("333");
  char buff[10];
  int ledState = msg.getString(0, buff, 10);
  Serial.print("/info: ");
  Serial.println(buff);
}

void loop() {

  //check for new udp-packet:
  OSCMessage msgIN;
  int size;
  if((size = udp.parsePacket())>0){
    Serial.println("1111");
    while(size--)
      msgIN.fill(udp.read());
    if(!msgIN.hasError()){
      Serial.println("2222");
      msgIN.route("/info", led);
    }
  }
}
