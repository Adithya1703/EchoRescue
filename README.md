# EchoRescue: Embedded Emergency Response System 🚨

**EchoRescue** is a compact, portable embedded system designed for emergency detection and response. It uses sensor fusion and wireless communication to detect critical events (like falls or gestures), capture surrounding data, and send alerts including GPS location to a predefined number via SMS.

## 🔧 Features

- **Fall Detection** using MPU6050 (accelerometer + gyroscope)
- **Gesture-based Trigger** using APDS-9930
- **Photo Capture** on Event Trigger via ESP32-CAM
- **Location Tracking** using NEO-6M GPS
- **Emergency SMS** with photo + location using SIM800L
- **Manual SOS Button** for user-triggered alerts
- **Haptic Feedback** using Vibration Motor
- **Battery Powered** using 9V + XL6009/TP4056

## 📦 Hardware Used

| Component       | Function |
|----------------|----------|
| ESP32 / ESP8266 | Controller |
| MPU6050         | Fall detection |
| APDS-9930       | Gesture + Light sensing |
| ESP32-CAM       | Photo capture |
| SIM800L         | GSM Module (SMS sending) |
| NEO-6M GPS      | Location |
| Relay (optional)| Trigger buzzer/LED |
| Vibration Motor | Haptic feedback |
| XL6009 / TP4056 | Power Management |
| Push Button     | Manual trigger |

## 🧠 Applications

- Personal safety for elderly or patients
- Wearable SOS alert device
- Remote location alert system

## 🚀 Getting Started

1. Clone the repo
2. Connect modules using circuit diagrams in `/circuit_diagrams`
3. Upload code to ESP32 using Arduino IDE
4. Power using 9V battery + XL6009 or TP4056 module

