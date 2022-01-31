#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>


enum MESSAGE{
	SYNC_ATTEMP,
	SYNC,
	OK
};


class CommunicationManager{
private:
	SoftwareSerial miBT;

	int8_t id;
	bool start = false;
public:
	CommunicationManager();

	void Init();
	void Sync();
	void Update();

	void SendMsg(MESSAGE msg);
	MESSAGE ReadMsg();

};