#pragma once
#include <Arduino.h>


enum JAVA_MESSAGE{
    JAVA_SYNC_ATTEMP = 0,
    JAVA_SYNC = 1,
    PAC_MAN_NORTH,
    PAC_MAN_EAST,
    PAC_MAN_SOUTH,
    PAC_MAN_WEST,

    JAVA_OK
};


class ServerManager{
private:


public:
    ServerManager();

    void SyncToJava();

    void SendMsg(JAVA_MESSAGE msg);
    JAVA_MESSAGE ReadMsg();
};