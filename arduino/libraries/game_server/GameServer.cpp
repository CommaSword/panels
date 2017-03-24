#include "PanelId.h"
#include "UIPEthernet.h"
#include "GameServer.h"

EthernetClient ethernetClient;
IPAddress serverIP(10,0,0,3);
char* initString = "{\"type\":\"hello\",\"id\":\"%s-%d\",\"state\":%d};";
char* stateString = "{\"type\":\"state\",\"state\":%d};";
char* noopString = "{\"type\":\"noop\"};";
char* clientId = "";
short reconnectNum = 0; // The sub-number for the connection
signed long lastReadoutTime = 0;


void GameServer::touchServer(){
	//Serial.println("Touching server");
	readFromServer();
	reconnectIfNeeded();
	writeState();
}

void GameServer::write(char* buffer){
	//Serial.println(buffer);
	ethernetClient.println(buffer);
	ethernetClient.flush();
}

void GameServer::writeState(){
	char* newString = (char*)malloc(27 * sizeof(char));
	sprintf(newString, stateString, GameServer::clientState);
	write(newString);
	free(newString);
}

void GameServer::writeInit(){
	char* newString = (char*)malloc(40 * sizeof(char));
	sprintf(newString, initString, clientId, reconnectNum, GameServer::clientState);
	write(newString);
	Serial.println(newString);
	Serial.println();
	free(newString);
}

void GameServer::reconnectIfNeeded(){
	//Serial.println("Check connection");
	// Check if we didnot have any indication from server for too long
	if (((signed long)(millis() - lastReadoutTime)) > 0)
	{
		connectToServer();
		lastReadoutTime = millis() + 5000;
	}
	// Checks if we are connected to the server. If not reconnects us to it.
	int innertime = 0;
	while(ethernetClient.connected()==0)
	{
		Serial.println("Not connected");
		innertime += 10;
		delay(100);
		if (RECONNECTION_TIMEOUT - innertime < 0)
		{
			connectToServer();
		}
	}	

}

void GameServer::connectToServer(){
	// Timeout for connection to be availabe. Kill it and start a new one.
	Serial.println("Timeout waiting for connection");
	ethernetClient.stop();
	Serial.println("Resetting connection");
	ethernetClient.connect(serverIP,8888);
	writeInit();
	reconnectNum++;
	delay(500);
}

void GameServer::readFromServer(){
	short index = 0;
	short lastIndex = 0;
	char result[40];
	result[lastIndex] = '\0';
	while (ethernetClient.available()) {
		char c = ethernetClient.read();
		//Serial.print(c);
		if (c == ';')
		{
			lastIndex = index;
			index = 0;
		}
		else
		{
			result[index] = c;
		}
		index ++;
	}
	result[lastIndex] = '\0';
	if (lastIndex!=0)
	{
		Serial.print("data was sent from server = ");
		Serial.println(GameServer::serverState);
		// Data was actually recieved
		GameServer::serverState = atoi(result);
		// Update flag to indicate we got an answer from the server
		lastReadoutTime = millis() + 5000;
		
	}
	ethernetClient.flush();
}

void GameServer::init(char* id){
	Serial.println("Init");
	PanelIdManager manager = PanelIdManager();
	PanelId panelReadVal = manager.read();
	Ethernet.begin(panelReadVal.mac);
	clientId = id;
	connectToServer();
}


