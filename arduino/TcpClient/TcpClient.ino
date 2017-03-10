
#include <UIPEthernet.h>

EthernetClient client;
IPAddress serverIP(172,31,9,2);
signed long next;

void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  Ethernet.begin(mac);

  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  next = 0;
  client.connect(serverIP,8888);
  Serial.println("Client connected");

}

void loop() {
  Serial.println("Sending request");
  client.println("DATA from Client");
  int size;
  while((size = client.available()) > 0)
    {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg,size);
      Serial.write(msg,size);
      free(msg);
    }
    delay(3000);
}
