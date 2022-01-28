#pragma once
#include <Arduino.h>
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>

enum ENTITY_STATE{
	SYNC_ATTEMP,
	SYNC
};

struct RECIEVE_DATA_STRUCTURE{
	int8_t id; //robot id
	ENTITY_STATE ent_state;
};



class CommunicationManager{
private:
	RECIEVE_DATA_STRUCTURE myData;
	SoftwareSerial miBT;

	SoftEasyTransfer ET;

	bool start = false;
public:
	CommunicationManager();

	void Init();
	void Update();

	bool Start();
};