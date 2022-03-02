//#include <BMI160Gen.h>
#include <CurieIMU.h>

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  /*// initialize device
  Serial.println("Initializing IMU device...");
    
  BMI160.begin(BMI160GenClass::I2C_MODE);
  uint8_t dev_id = BMI160.getDeviceID();
  Serial.print("DEVICE ID: ");
  Serial.println(dev_id, HEX);*/

  // Set the accelerometer range to 250 degrees/second
  /*BMI160.setGyroRange(250);
  BMI160.setGyroRate(25);
  BMI160.setAccelerometerRange(2);
  BMI160.setAccelerometerRate(25);
  Serial.println("Initializing IMU device...done.");
*/

  Serial.println("Curie Init");
  //CurieIMU.begin();

  Serial.println("Internal sensor offsets BEFORE calibration...");
  Serial.print(CurieIMU.getXAccelOffset()); 
  Serial.print("\t"); // -76
  Serial.print(CurieIMU.getYAccelOffset()); 
  Serial.print("\t"); // -235
  Serial.print(CurieIMU.getZAccelOffset()); 
  Serial.print("\t"); // 168
  Serial.print(CurieIMU.getXGyroOffset()); 
  Serial.print("\t"); // 0
  Serial.print(CurieIMU.getYGyroOffset()); 
  Serial.print("\t"); // 0
  Serial.println(CurieIMU.getZGyroOffset());
  Serial.println("About to calibrate. Make sure your board is stable and upright");
  delay(1000);
  
}

void loop() {

  int gxRaw, gyRaw, gzRaw;         // raw gyro values

  // read raw gyro measurements from device
  CurieIMU.readGyro(gxRaw, gyRaw, gzRaw);

  Serial.println(gzRaw);

  //delay(250);
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;

  return g;
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2 g range
  // -2 g maps to a raw value of -32768
  // +2 g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}
