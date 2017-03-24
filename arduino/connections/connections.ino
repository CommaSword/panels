
#include <UIPEthernet.h>
#include <PanelId.h>
#include <GameServer.h>

GameServer server = GameServer();
char* aaa = "aaa";
char* bbb = "first";
void setup() {
  Serial.begin(9600);;
  server.init();
}

void loop() {
  Serial.println("Sending request");
  server.write(aaa);
  server.read(&bbb);
  Serial.println(bbb);
  delay(400);
}
