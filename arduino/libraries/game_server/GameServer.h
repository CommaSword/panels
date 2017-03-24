#ifndef GameServer_h
#define GameServer_h

#define RECONNECTION_TIMEOUT 1000
#define MESSAGE_LENGTH 100

class GameServer{
public:
    void read(char** buffer);
    void write(char* buffer);
    void init();
};

#endif