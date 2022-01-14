#include "GyroscopeController.h"

Simple_MPU6050 myMpu;

void ShowValues(int16_t *gyro, int16_t *accel, int32_t *quat, uint32_t *timestamp){
    uint8_t SpamDelay = 100;      // demora para escribir en monitor serie de 100 mseg
    Quaternion q;         // variable necesaria para calculos posteriores
    VectorFloat gravity;        // variable necesaria para calculos posteriores
    float ypr[3] = { 0, 0, 0 };     // array para almacenar valores de yaw, pitch, roll
    float xyz[3] = { 0, 0, 0 };     // array para almacenar valores convertidos a grados de yaw, pitch, roll
    spamtimer(SpamDelay) {      // si han transcurrido al menos 100 mseg entonces proceder
        myMpu.GetQuaternion(&q, quat);    // funcion para obtener valor para calculo posterior
        myMpu.GetGravity(&gravity, &q);   // funcion para obtener valor para calculo posterior
        myMpu.GetYawPitchRoll(ypr, &q, &gravity); // funcion obtiene valores de yaw, ptich, roll
        myMpu.ConvertToDegrees(ypr, xyz);   // funcion convierte a grados sexagesimales
        Serial.printfloatx(F("Yaw")  , xyz[0], 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje Z, yaw
        Serial.printfloatx(F("Pitch"), xyz[1], 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje Y, pitch
        Serial.printfloatx(F("Roll") , xyz[2], 9, 4, F(",   "));  // muestra en monitor serie rotacion de eje X, roll
        Serial.println();       // salto de linea
    }
}

GyroscopeController::GyroscopeController(){

}

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
}
