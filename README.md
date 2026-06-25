# 🪖 SMART HELMET – IoT-Based Rider Safety & Intelligent Vehicle Access System

### *An Integrated Helmet Authentication, Accident Detection, and Smart Physical Ignition Protection System*

---

# 📖 Project Overview

The **Smart Helmet** is an IoT-enabled rider safety system developed to improve road safety by combining intelligent rider authentication, alcohol detection, accident monitoring, and physical vehicle access control into a single integrated platform.

Unlike conventional smart helmets that only disable the ignition electronically, this system introduces a **servo-actuated mechanical locking mechanism** that physically blocks the vehicle's ignition key slot. The rider can access the ignition only after the helmet confirms that it is being worn correctly and that no alcohol has been detected.

In addition, the system continuously monitors rider movement using an inertial sensor. If a severe impact or accident is detected, the rider's live GPS location is transmitted automatically to predefined emergency contacts through Telegram, enabling faster emergency response.

---

# 🎯 Project Objectives

* Develop a reliable rider authentication mechanism using helmet wear detection.
* Prevent vehicle operation when alcohol consumption is detected.
* Physically secure the ignition key inlet using a servo-controlled locking mechanism.
* Detect accidents in real time using motion analysis.
* Automatically transmit emergency alerts with GPS coordinates to family members via Telegram.
* Improve rider safety through proactive accident prevention and rapid emergency notification.

---

# ✨ Key Features

### 🛡 Helmet Authentication

An infrared proximity sensor verifies whether the rider is wearing the helmet correctly before vehicle access is granted.

### 🍺 Alcohol Detection

The MQ-3 alcohol sensor continuously checks the rider's breath. If alcohol concentration exceeds the defined threshold, ignition access remains locked.

### 🔐 Physical Ignition Protection

Instead of disconnecting the ignition circuit, a servo motor controls a mechanical shutter that physically blocks the ignition key slot, preventing unauthorized or unsafe vehicle operation.

### 🚨 Intelligent Accident Detection

The MPU6050 accelerometer and gyroscope monitor abnormal acceleration and impact. Upon detecting a crash, the emergency protocol is triggered automatically.

### 📍 Live Emergency Notification

The ESP32 retrieves the rider's GPS coordinates through the companion mobile application and sends an emergency message containing the live location to registered contacts using the Telegram Bot API.

---

# 🛠 Hardware Components

| Component          | Purpose                                               |
| ------------------ | ----------------------------------------------------- |
| Arduino Uno / Nano | Helmet-side microcontroller                           |
| ESP32              | Vehicle-side controller with Wi-Fi connectivity       |
| MPU6050            | Accident detection using acceleration and orientation |
| MQ-3 Sensor        | Alcohol detection                                     |
| IR Sensor          | Helmet wear detection                                 |
| RF 433 MHz Module  | Wireless communication between helmet and vehicle     |
| Servo Motor        | Mechanical ignition key blocker                       |

---

# 🏗 System Architecture

```text
                 HELMET UNIT
            ┌─────────────────────┐
            │ Arduino Uno / Nano  │
            ├─────────────────────┤
            │ IR Sensor           │
            │ MQ-3 Alcohol Sensor │
            │ MPU6050 IMU         │
            │ RF Transmitter      │
            └──────────┬──────────┘
                       │
               Wireless RF Signal
                       │
                       ▼
             VEHICLE CONTROL UNIT
        ┌───────────────────────────┐
        │ ESP32 Controller          │
        ├───────────────────────────┤
        │ RF Receiver               │
        │ Servo Motor               │
        │ Wi-Fi Communication       │
        └──────────┬────────────────┘
                   │
                   ▼
        Mobile Application (MIT App)
                   │
                   ▼
       GPS Location + Telegram Alert
```

---

# ⚙ System Workflow

1. The helmet verifies whether it is properly worn using the IR sensor.
2. The MQ-3 sensor checks the rider for alcohol consumption.
3. If both safety conditions are satisfied, an encrypted RF signal is transmitted to the vehicle unit.
4. The ESP32 receives the authorization signal and rotates the servo motor to uncover the ignition key slot.
5. During the ride, the MPU6050 continuously monitors sudden impacts and abnormal motion.
6. If an accident is detected, the ESP32 acquires the rider's GPS location through the mobile application.
7. An emergency alert containing the rider's location is immediately sent to predefined contacts via Telegram.

---

# 💻 Software Stack

| Software           | Purpose                        |
| ------------------ | ------------------------------ |
| Arduino IDE        | Embedded firmware development  |
| MIT App Inventor   | Android companion application  |
| Telegram Bot API   | Emergency notification service |
| RCSwitch Library   | RF communication               |
| MPU6050 Library    | Motion sensing                 |
| ESP32Servo Library | Servo motor control            |

---

# 📂 Project Structure

```text
Smart-Helmet/
│
├── helmet/
│   ├── accident_detection.ino
│   ├── helmet_controller.ino
│
├── vehicle/
│   ├── keyhole_control.ino
│   ├── telegram_alert.ino
│
├── docs/
│   ├── wiring_diagram.png
│   ├── circuit_diagram.png
│   ├── mit_app_blocks.png
│   └── system_architecture.png
│
├── images/
│   ├── prototype.jpg
│   ├── helmet_unit.jpg
│   └── vehicle_unit.jpg
│
└── README.md
```

---

# 🚀 Future Enhancements

* GSM module for operation without a smartphone.
* Real-time cloud dashboard for ride monitoring.
* Crash severity classification using machine learning.
* Face recognition-based rider authentication.
* Mobile application with ride analytics and health monitoring.
* Cloud database for accident history and vehicle logs.

---

# 📌 Conclusion

The Smart Helmet demonstrates how embedded systems and IoT can be combined to create a comprehensive rider safety solution. By integrating intelligent authentication, alcohol detection, physical ignition protection, accident detection, and automated emergency communication, the system significantly enhances rider security while minimizing the likelihood of unsafe vehicle operation. The modular architecture also allows future integration with cloud platforms and advanced AI-based safety features.

```text
╔══════════════════════════════════════════════════════════════╗
║             SMART HELMET SYSTEM - VERSION 1.0               ║
║                                                             ║
║     Rider Verified ✓   Vehicle Secured ✓   Alert Ready ✓    ║
╚══════════════════════════════════════════════════════════════╝
```
