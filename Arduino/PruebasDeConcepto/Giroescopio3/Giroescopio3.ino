#include <MadgwickAHRS.h>
#include <BMI160Gen.h>

Madgwick filter;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
    
  BMI160.begin(BMI160GenClass::I2C_MODE);
  uint8_t dev_id = BMI160.getDeviceID();
  Serial.print("DEVICE ID: ");
  Serial.println(dev_id, HEX);

  // Set the accelerometer range to 250 degrees/second
  BMI160.setGyroRange(250);
  BMI160.setGyroRate(25);
  BMI160.setAccelerometerRange(2);
  BMI160.setAccelerometerRate(25);
  Serial.println("Initializing IMU device...done.");

  //filter.begin(25);

  Serial.println("Curie Init");
}

void loop() {
  int gxRaw, gyRaw, gzRaw;         // raw gyro values
  int axRaw, ayRaw, azRaw;

  float gx, gy, gz;
  float ax, ay, az;

  // read raw gyro measurements from device
  BMI160.readGyro(gxRaw, gyRaw, gzRaw);
  BMI160.readAccelerometer(axRaw, ayRaw, azRaw);

  // convert the raw gyro data to degrees/second
  gx = convertRawGyro(gxRaw);
  gy = convertRawGyro(gyRaw);
  gz = convertRawGyro(gzRaw);
  ax = convertRawAcceleration(axRaw);
  ay = convertRawAcceleration(ayRaw);
  az = convertRawAcceleration(azRaw);


  float yaw = lsb_to_ms2(gz, 8, 16);

  
  Serial.println(yaw);

  //delay(100);
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







#define GRAVITY_EARTH   (9.80665f) /* Earth's gravity in m/s^2 */
#define RAD             (57.2957805f)
#define INV_RAD         (0.01745329f)

float lsb_to_ms2(int16_t val, float g_range, uint8_t bit_width)
{
  float half_scale = (float)(1 << bit_width) / 2.0f;

  return GRAVITY_EARTH * val * g_range / half_scale;
}
