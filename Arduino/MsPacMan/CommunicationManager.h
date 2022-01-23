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
	SoftwareSerial miBT;

	SoftEasyTransfer ET;
public:
	CommunicationManager();

	void Init();
	void Update();
};