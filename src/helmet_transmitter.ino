#include <Wire.h>
#include <math.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const int MPU = 0x68;      // MPU6050 I2C address
const int MQ3 = A0;        // MQ3 analog pin
const int irPin = 2;       // IR sensor pin (LOW = helmet worn)

// MPU variables
int16_t AcX, AcY, AcZ;
float accelMagnitude;

// Thresholds
const float ACCIDENT_THRESHOLD = 25000.0;
const int ALCOHOL_THRESHOLD = 350;

void setup() {
  Serial.begin(9600);

  // RF
  mySwitch.enableTransmit(12);

  // IR
  pinMode(irPin, INPUT);

  // MQ3
  pinMode(MQ3, INPUT);

  // MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("System Ready");
}

void loop() {
------------------------------------------------
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  float x = (float)AcX;
  float y = (float)AcY;
  float z = (float)AcZ;

  accelMagnitude = sqrt(x*x + y*y + z*z);

  Serial.print("Accel Magnitude: ");
  Serial.println(accelMagnitude);

  if (accelMagnitude > ACCIDENT_THRESHOLD) {
    Serial.println("⚠️ ACCIDENT DETECTED → Sending 12");
    mySwitch.send(12, 24);       // Accident code
    delay(1000);
    return;                      // Skip remaining checks
  }


  int mqValue = analogRead(MQ3);
  bool alcoholPresent = (mqValue > ALCOHOL_THRESHOLD);

  Serial.print("Alcohol Value: ");
  Serial.println(mqValue);


  int irValue = digitalRead(irPin);
  bool helmetWorn = (irValue == LOW);   // LOW = helmet worn

  Serial.print("Helmet: ");
  Serial.println(helmetWorn ? "WORN" : "NOT WORN");

 
  if (!alcoholPresent && helmetWorn) {
    Serial.println("SAFE → Sending 1234");
    mySwitch.send(1234, 24);
  }
  else {
    Serial.println("UNSAFE → Sending 123");
    mySwitch.send(123, 24);
  }

  delay(800);
}
