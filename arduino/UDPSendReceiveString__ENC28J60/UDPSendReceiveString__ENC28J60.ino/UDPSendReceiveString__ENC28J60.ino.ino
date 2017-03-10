#include <UIPEthernet.h>
#define UDP_TX_PACKET_MAX_SIZE 100

EthernetUDP udp;
unsigned long next;
IPAddress pongIP(192, 168, 0, 1);
//IPAddress selfIP(192, 168, 0, 1);
IPAddress selfIP(192,168,0,1);
//byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x00 };
byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };

char  ReplyBuffer[] = "acknowledged";       // a string to send back
char  originalPing[] = "Ping"; 
unsigned int localPort = 8888;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

void setup() {

  Serial.begin(9600);
  
  Ethernet.begin(myMac, selfIP);

  Serial.println(Ethernet.localIP());

  
  if (Ethernet.localIP() !=  pongIP){
    Serial.println("Sending data to pong");
    udp.beginPacket(pongIP, localPort);
    udp.write(originalPing);
    udp.endPacket();
    udp.stop();
  }
  
}

void loop() {

  int success;
  int len = 0;
  int packetSize = udp.parsePacket();
  Serial.println("Listening...");
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(udp.remotePort());

    // read the packet into packetBufffer
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply to the IP address and port that sent us the packet we received
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write(ReplyBuffer);
    udp.endPacket();
  }
  udp.stop();
  
  delay(1000);
}
