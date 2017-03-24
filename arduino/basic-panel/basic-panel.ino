#include <PanelId.h>
#include <GameServer.h>

GameServer server = GameServer();

int button = 7; // push button pin
int led = 8; //red led  pin
int buttonState; //indicates the button state 0/1

int buttonPressTime = 0;
char* id = "3";
long timeSinceFixed = 0; //The timestamp of when the panel was fixed
int maxTime = 5000; // The timestamp to restart the ridlle from
int coolDown = 30000;
long keyDownTime = 0;
bool flag = false;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT); 
  server.init(id);
  delay(500);
  Serial.println(server.serverState);
}

void loop() {
  server.touchServer();
  if (server.serverState == 1)
  { 
    if (((signed long)(millis() - timeSinceFixed)) > coolDown)
    {
      server.clientState = 1; 
      buttonState = digitalRead(button);
      if(buttonState == 1){
        Serial.println("press");
        if (keyDownTime == 0){
          keyDownTime = millis();
        }
        if (((signed long)(millis() - keyDownTime)) > maxTime){
          Serial.println("Fixed");
          server.clientState = 0;
          timeSinceFixed = millis();
        }
      }
      else
      {
        keyDownTime = 0;
      }
    }
  }
  else // server.serverState == 0
  {
    server.clientState = 0;
  }
  
  // Set Hardware - LEDs
  if (server.clientState == 0){
    digitalWrite(led,LOW); 
  }
  else
  {
    digitalWrite(led,HIGH);
  }
  delay(200);
}

