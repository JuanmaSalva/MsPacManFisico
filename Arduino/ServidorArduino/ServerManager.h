#pragma once
#include <Arduino.h>


enum JAVA_MESSAGE{
    JAVA_SYNC_ATTEMP,
    JAVA_SYNC,

    JAVA_OK
};


class ServerManager{
private:

    void SendMsg(JAVA_MESSAGE msg);
    JAVA_MESSAGE ReadMsg();

public:
    ServerManager();

    void SyncToJava();

};