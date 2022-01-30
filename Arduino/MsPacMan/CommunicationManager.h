#pragma once
#include <Arduino.h>
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>


enum ENTITY_STATE{
	SYNC_ATTEMP,
	SYNC,
	LINE_TRACKER_INITIALIZED,
	GYROSCOPE_INITIALIZED,
	MOTORS_INITIALIZES,
};

struct MESSAGE{
	int8_t id; //robot id
	ENTITY_STATE ent_state;
};

struct MESSAGE_RESPONSE{
	bool ok;
};


class CommunicationManager{
private:
	MESSAGE recivMsg;
	MESSAGE_RESPONSE sendMsg;

	SoftwareSerial miBT;

	SoftEasyTransfer et_in;
	SoftEasyTransfer et_out;

	int8_t id;
	bool start = false;
public:
	CommunicationManager();

	void Init();
	void Sync();
	void Update();
	//void SendMsg(ENTITY_STATE msg);
	void WaitApproval();

	bool Start();
};