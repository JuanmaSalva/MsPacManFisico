#pragma once
#include <Arduino.h>
#include <SoftEasyTransfer.h>
#include <SoftwareSerial.h>


struct RECIEVE_DATA_STRUCTURE{
	int8_t id;
	int8_t number;
};


class CommunicationManager{
private:
	RECIEVE_DATA_STRUCTURE myData;

	SoftEasyTransfer ET;

	bool start = false;
public:
	CommunicationManager();

	void Init();
	void Update();

	bool Start();
};