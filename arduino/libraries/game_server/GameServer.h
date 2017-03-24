#ifndef GameServer_h
#define GameServer_h

#define RECONNECTION_TIMEOUT 1000
#define MESSAGE_LENGTH 100

class GameServer{
public:
	int serverState = 0;
	int clientState = 0;
	void touchServer();
    void init(char* id);
	
private:
	void writeState();
	void readFromServer();
	void reconnectIfNeeded();
	void writeInit();
	void write(char* buffer);
	void connectToServer();
};

#endif