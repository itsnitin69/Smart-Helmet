#include <RCSwitch.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h" 
RCSwitch mySwitch = RCSwitch();
Servo myServo;

#define SERVO_PIN 14   // Servo control pin
#define RX_PIN 27      // RF receiver pin

bool servoActive = false;
int currentAngle = 90;               // start at center so +/- 30° works
const int MOVE_STEP = 30;            // how many degrees to move
const bool INVERT_DIRECTION = true;  // set true if increasing angle currently moves LEFT
BluetoothSerial ESP_BT; 
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(RX_PIN);  // RF receiver on GPIO27
  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);
  Serial.println("ESP32 Ready (RC-Switch + Servo)");
  ESP_BT.begin("ESP32_Control");
}

// smooth move from currentAngle -> target (1° steps)
void smoothMoveTo(int target) {
  target = constrain(target, 0, 180);
  int step = (target > currentAngle) ? 1 : -1;
  while (currentAngle != target) {
    currentAngle += step;
    myServo.write(currentAngle);
    delay(10); // change this to speed up/slow down movement
  }
}

void loop() {
  if (mySwitch.available()) {
    long value = mySwitch.getReceivedValue();
    if (value != 0) {
      Serial.print("Received: ");
      Serial.println(value);
    if (value == 12){
      ESP_BT.write(value);
      Serial.println("accident detction send");

    }

      if (value == 1234) {
        if (!servoActive) {   // move only once per activation
          Serial.println("1234 detected → move RIGHT by 30° (relative)");
          int delta = INVERT_DIRECTION ? -MOVE_STEP : MOVE_STEP;
          smoothMoveTo(constrain(currentAngle + delta, 0, 180));
          servoActive = true;
        }
      } else {
        if (servoActive) {    // on other signal, move back by 30°
          Serial.println("Other signal detected → move BACK by 30° (relative)");
          int delta = INVERT_DIRECTION ? MOVE_STEP : -MOVE_STEP;
          smoothMoveTo(constrain(currentAngle + delta, 0, 180));
          servoActive = false;
        }
      }
    }
    mySwitch.resetAvailable();
  }
}
