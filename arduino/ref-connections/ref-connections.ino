
#include <PanelId.h>
#include <GameServer.h>

GameServer server = GameServer();
short state = 1;
char* id = "2";

void setup() {
  Serial.begin(9600);;
  server.init(id);
  delay(500);
}

void loop() {
  Serial.println("Sending request");
  server.touchServer();
  Serial.println(server.serverState);
  Serial.println(server.clientState);
}
