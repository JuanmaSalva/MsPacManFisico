#include "GyroscopeController.h"

Simple_MPU6050 myMpu;
#define DRIFT 3.0
float currentYaw = 0;
float previousYaw = 0;
float positiveCurrentYaw;

GyroscopeController::GyroscopeController(){
	acumulatedYaw = 0;
}


float GetDelta(float driftedYaw){
	//drifed delta
    float delta = (driftedYaw - previousYaw);
    if(delta > 300) delta -= 360;
    else if (delta < -300) delta += 360;

    //undrif delta
    float aux = (delta * DRIFT) / 360.0;
    delta -= aux;

    return delta;
}

float CalculateRealAngle(float driftedYaw){
	float delta = GetDelta(driftedYaw);
    previousYaw = driftedYaw;

    currentYaw += delta;
	
	//pasamos del rango -180 a 180
    if(currentYaw < -180.0)
      currentYaw = 360 + currentYaw;
    else if(currentYaw > 180)
      currentYaw = currentYaw - 360;

	//pasamos a numero positivos
	if(currentYaw < 0)
		currentYaw = 360 + currentYaw;
	else 
		currentYaw = currentYaw;

	return currentYaw;
}

/**
 * @brief Saca y calcula los datos del giroescopio
 * 
 * @param gyro valores del giroescopio
 * @param accel valores del acelerómetro
 * @param quat valor del quaternion actual
 * @param timestamp tiempo desde la última toma de datos
 */
void ShowValues(int16_t *gyro, int16_t *accel, int32_t *quat, uint32_t *timestamp){
	Quaternion q;
	VectorFloat gravity;
	float ypr[3] = { 0, 0, 0 };
	float xyz[3] = { 0, 0, 0 };
	myMpu.GetQuaternion(&q, quat);
	myMpu.GetGravity(&gravity, &q);
	myMpu.GetYawPitchRoll(ypr, &q, &gravity);
	myMpu.ConvertToDegrees(ypr, xyz);
	
	if(xyz[0] < 0)
		positiveCurrentYaw = 360 + xyz[0];
	else 
		positiveCurrentYaw = xyz[0];

	/*float driftedYaw = 0;
	if(xyz[0] < 0)
		driftedYaw = 360 + xyz[0];
	else 
		driftedYaw = xyz[0];

	positiveCurrentYaw = CalculateRealAngle(driftedYaw);*/
}





/**
 * @brief Inicializa y calibra el giroescopio
 * Este proceso puede durar unos segundos
 */
void GyroscopeController::Init(){
	uint8_t val;
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE  // activacion de bus I2C a 400 Khz
	Wire.begin();
	Wire.setClock(400000);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif
	while (!Serial);      // espera a enumeracion en caso de modelos con USB nativo
	Serial.println(F("Inicio:"));   // muestra texto estatico
#ifdef OFFSETS                // si existen OFFSETS
	Serial.println(F("Usando Offsets predefinidos"));     // texto estatico
	myMpu.SetAddress(MPU6050_ADDRESS_AD0_LOW).load_DMP_Image(OFFSETS);  // inicializacion de sensor

#else                   // sin no existen OFFSETS
	Serial.println(F(" No se establecieron Offsets, haremos unos nuevos.\n" // muestra texto estatico
					" Colocar el sensor en un superficie plana y esperar unos segundos\n"
					" Colocar los nuevos Offsets en #define OFFSETS\n"
					" para saltar la calibracion inicial \n"
					" \t\tPresionar cualquier tecla y ENTER"));
	myMpu.SetAddress(MPU6050_ADDRESS_AD0_LOW).CalibrateMPU().load_DMP_Image();  // inicializacion de sensor
#endif
	myMpu.on_FIFO(ShowValues);   // llamado a funcion mostrar_valores si memoria FIFO tiene valores
	
}


void GyroscopeController::Update(){
	myMpu.dmp_read_fifo();
	
	Serial.println(positiveCurrentYaw);

	//UpdateAdverageYaw();
}

void GyroscopeController::UpdateAdverageYaw(){
	if(targetYaw % 360 == 0){
		if(positiveCurrentYaw > 180)
			acumulatedYaw += (360 - positiveCurrentYaw);
		else     
			acumulatedYaw += positiveCurrentYaw;
	}
	else 
		acumulatedYaw += positiveCurrentYaw;
	numberOfSamples++;
	adverageYaw = acumulatedYaw / numberOfSamples;
	//Serial.println(adverageYaw);
}

float GyroscopeController::GetCurrentYaw(){
	return positiveCurrentYaw;
}

float GyroscopeController::GetAdverageYaw(){
	if(adverageYaw < 0)
		return adverageYaw;
	else
		return adverageYaw;
}

/**
 * @brief Resetea el Yaw promedio 
 */
void GyroscopeController::ResetYaw(){
	numberOfSamples = 0;
	acumulatedYaw = 0;
}

void GyroscopeController::SetTargetYaw(int newTargetYaw){
	targetYaw = newTargetYaw;
}
