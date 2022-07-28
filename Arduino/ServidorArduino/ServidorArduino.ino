#include "CommunicationManager.h"
#include "ServerManager.h"

CommunicationManager* communicationManager;
ServerManager* serverManager;

//pines para la led rgb
int red = 9;
int green = 10;
int blue = 11;


/**
 * @brief Se inicializan todos los pines del Arduino 
 */
void Init(){
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Inicializamos");

	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	
	analogWrite(red, 255);
	analogWrite(green, 0);
	analogWrite(blue, 0);
}

void setup() {	
	Init();

	//inicialización y sincronización de la comunicación con el robot
	communicationManager = new CommunicationManager();
	communicationManager->Init();
	communicationManager->Sync();
	communicationManager->WaitForRobotToInitialize();


	analogWrite(red, 0);
	analogWrite(green, 0);
	analogWrite(blue, 255);


	// serverManager = new ServerManager();
	// serverManager->SyncToJava();


	// serverManager->WaitForMsg(JAVA_MESSAGE::JAVA_START);
	// communicationManager->SendMsg(MESSAGE::START);


	// analogWrite(red, 0);
	// analogWrite(green, 255);
	// analogWrite(blue, 0);
}


/**
 * @brief Se reciben y se procesan los mensajes del MsPacManEngine
 * Actualmente solo se imprimen por el monitor serial ya que el recorrido
 * es fijo para facilitar la depuración en el robot
 */
void MsPacManEngineCommunication(){
	if(Serial.available()){
		JAVA_MESSAGE msg = serverManager->ReadMsg();
		
		if(msg == PAC_MAN_UP){
			Serial.println("Up");
		}
		else if(msg == PAC_MAN_RIGHT){
			Serial.println("Right");	
		}
		else if(msg == PAC_MAN_DOWN){
			Serial.println("Down");	
		}
		else if(msg == PAC_MAN_LEFT){
			Serial.println("Left");	
		}
	}
}


/**
 * @brief Se lee y se procesan de los mensajes de debug recibidos desde el robot
 **/
void DebugLed(){
	if(communicationManager->MsgAvailable()){
		Serial.println("Mensaje Recibido");
		MESSAGE msg = communicationManager->ReadMsg();

		if(msg == RED_LED){
			analogWrite(red, 255);
			analogWrite(green, 0);
			analogWrite(blue, 0);
		}
		else if(msg == BLUE_LED){
			analogWrite(red, 0);
			analogWrite(green, 0);
			analogWrite(blue, 255);			
		}
		else if(msg == YELLOW_LED){
			analogWrite(red, 255);
			analogWrite(green, 255);
			analogWrite(blue, 0);			
		}
		else if(msg == CIAN_LED){
			analogWrite(red, 0);
			analogWrite(green, 255);
			analogWrite(blue, 255);			
		}
		else if(msg == MAGENTA_LED){
			analogWrite(red, 255);
			analogWrite(green, 0);
			analogWrite(blue, 255);			
		}
		else if(msg == WHITE_LED){
			analogWrite(red, 255);
			analogWrite(green, 255);
			analogWrite(blue, 255);			
		}
		else if(msg == GREEN_LED){
			analogWrite(red, 0);
			analogWrite(green, 255);
			analogWrite(blue, 0);
		}
	}
}

void loop() {
	// MsPacManEngineCommunication();

	// DebugLed();
}
