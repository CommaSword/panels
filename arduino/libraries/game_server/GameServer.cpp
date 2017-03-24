#include "PanelId.h"
#include "UIPEthernet.h"
#include "GameServer.h"

EthernetClient ethernetClient;
IPAddress serverIP(172,31,9,2);

void reconnectIfNeeded(){
	ethernetClient.flush();
	int innertime = 0;
	while(ethernetClient.available()==0)
	{
		innertime += 10;
		delay(10);
		if (RECONNECTION_TIMEOUT - innertime < 0)
		{
		  Serial.println("No answer from server");
		  ethernetClient.stop();
		  Serial.println("Resetting connection");
		  ethernetClient.connect(serverIP,8888);
		  break;
		}
	}
}

void GameServer::read(char** buffer){
	reconnectIfNeeded();
	int size;
	while((size = ethernetClient.available()) > 0)
	{
		char* msg = (char*)malloc(size);
		size = ethernetClient.read(msg,size);
		Serial.write(msg,size);
		Serial.println(msg);
		*buffer = msg;
		free(msg);
	}
}
void GameServer::write(char buffer[]){
	 ethernetClient.flush();
	 ethernetClient.println("DATA from Client");
}
void GameServer::init(){
	PanelIdManager manager = PanelIdManager();
	PanelId panelReadVal = manager.read();
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
	ethernetClient.connect(serverIP,8888);
	Serial.println("Client connected");
	
}


