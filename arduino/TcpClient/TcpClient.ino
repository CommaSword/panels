
#include <UIPEthernet.h>
#include <PanelId.h>

EthernetClient client;
IPAddress serverIP(172,31,9,2);
PanelIdManager manager = PanelIdManager();
int connectionTime = 1000;
int innertime;

void setup() {

  Serial.begin(9600);
  PanelId panelReadVal = manager.read();
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  Ethernet.begin(panelReadVal.mac);

//  Serial.print("localIP: ");
//  Serial.println(Ethernet.localIP());
//  Serial.print("subnetMask: ");
//  Serial.println(Ethernet.subnetMask());
//  Serial.print("gatewayIP: ");
//  Serial.println(Ethernet.gatewayIP());
//  Serial.print("dnsServerIP: ");
//  Serial.println(Ethernet.dnsServerIP());
  Serial.println("Connecting to server");
  client.connect(serverIP,8888);
  Serial.println("Client connected");
}

void loop() {
  innertime = 0;
  bool resetConnection = false;
  Serial.println("Sending request");
  client.flush();
  client.println("DATA from Client");
  if (connectionTime - innertime > 0)
    {
      while(client.available()==0)
      {
        innertime += 10;
        delay(10);
        if (connectionTime - innertime < 0){
          Serial.println("No answer from server");
          resetConnection = true;
          goto reset;
        }
      }
      int size;
      while((size = client.available()) > 0)
      {
        uint8_t* msg = (uint8_t*)malloc(size);
        size = client.read(msg,size);
        Serial.write(msg,size);
        free(msg);
      }
    }
    reset:
    if (resetConnection){
      Serial.println("Resetting connection");
      client.stop();
      client.connect(serverIP,8888);
    }
    delay(400);
}
