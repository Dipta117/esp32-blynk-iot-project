
# ESP32 IoT Smart Monitoring System with Blynk

## 📋 Project Overview

An IoT-based environmental monitoring system using the ESP32 microcontroller that demonstrates bidirectional communication with the Blynk mobile app. The system reads temperature and humidity data and allows remote LED control through cloud connectivity.

---

## 🎯 Project Objectives

 Implement IoT system with ESP32 and DHT22 sensor
 Demonstrate READ operations from mobile app to hardware
 Monitor real-time environmental data through cloud platform
 Showcase bidirectional communication between hardware and mobile app

---

## 🛠️ Technologies Used

 Hardware: ESP32 Dev Module, DHT22 Sensor, LED
 Software: PlatformIO, Arduino Framework
 IoT Platform: Blynk Cloud Services
 Simulation: Wokwi ESP32 Simulator
 Communication: WiFi, Blynk Cloud

---

## 📁 Project Structure

```
esp32-blynk-iot-project/
│
├── src/
│   └── main.cpp                 # Main application code
├── include/                     # Header files
├── lib/                         # Custom libraries
├── diagram.json                 # Wokwi simulation diagram
├── wokwi.toml                   # Wokwi configuration
├── platformio.ini               # PlatformIO configuration
└── README.md                    # Project documentation
```

---

## 🚀 Quick Start

### Prerequisites

 VS Code with PlatformIO extension
 Blynk IoT mobile app
 Wokwi account (for simulation)

### Installation Steps

1. Clone the Repository

   ```bash
   git clone https://github.com/Dipta117/esp32-blynk-iot-project.git
   cd esp32-blynk-iot-project
   ```

2. Open in PlatformIO

    Launch VS Code
    Open the project folder
    PlatformIO should automatically detect the project

3. Configure Blynk Credentials
   Update the following in `src/main.cpp`:

   ```cpp
   #define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
   #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
   #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
   ```

4. Build the Project

    Click the ✓ (Build) button in PlatformIO
    Or use the terminal:

     ```bash
     pio run
     ```

---

## 🎮 Running the Simulation

### Method 1: Wokwi Simulation (Recommended)

1. Ensure all files are in the project root:

    `diagram.json`
    `wokwi.toml`
    `platformio.ini`

2. Build the Project

    Click the ✓ Build button in PlatformIO

3. Start the Simulation

    Press `Ctrl + Shift + P`
    Type: `Wokwi: Start Simulator`
    Press Enter

### Method 2: Physical Hardware

1. Connect Components

    DHT22: VCC → 3.3V, GND → GND, DATA → GPIO4
    LED: Anode → GPIO23, Cathode → GND (with resistor)

2. Upload Code

    Connect ESP32 via USB
    Click the → (Upload) button in PlatformIO

---

## 📱 Blynk App Setup

### Step 1: Download Blynk App

 Android: Play Store → “Blynk IoT”
 iOS: App Store → “Blynk IoT”

### Step 2: Create Account & Template

1. Create a new Blynk account
2. Go to Templates → Create New
3. Set the following:

    Name: `ESP32 IoT Monitor`
    Hardware: `ESP32`
    Connection: `Wi-Fi`

### Step 3: Add Widgets

| Virtual Pin | Widget | Purpose             |
| ----------- | ------ | ------------------- |
| V0      | Button | LED ON/OFF Control  |
| V1      | Label  | LED Status Display  |
| V2      | Label  | Temperature Display |
| V3      | Label  | Humidity Display    |

### Step 4: Device Setup

1. Create a new device from the template
2. Copy the Auth Token
3. Update the token in `src/main.cpp`

---

## 🔧 Configuration Files

### `platformio.ini`

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps = 
    blynk/Blynk@^1.3.2
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
```

### `wokwi.toml`

```toml
[wokwi]
version = 1

[[parts]]
type = "esp32"

[[parts]]
type = "dht22"
connect = "D4"

[[parts]]
type = "led"
connect = "D23"
```

---

## 📊 Features Demonstrated

### ✅ READ Operations (Mobile App → ESP32)

 V0: Button press to control LED
 Real-time command processing from mobile app

### ✅ WRITE Operations (ESP32 → Mobile App)

 V2: Temperature data transmission
 V3: Humidity data transmission
 V1: LED status updates

### ✅ Additional Features

 Real-time sensor data monitoring
 Cloud connectivity via Blynk
 Error handling and data validation
 Non-blocking operation using timers

---

## 🎓 Learning Outcomes

### Technical Skills

 ESP32 programming with Arduino framework
 IoT cloud communication protocols
 Sensor integration and data processing
 Mobile app integration with hardware
 Simulation-based development

### IoT Concepts

 Bidirectional cloud communication
 Remote device control
 Real-time data monitoring
 Wireless sensor networks

---

## 🔍 Expected Output

### Serial Monitor

```
🎉 SUCCESS: Connected to Blynk Server!
📱 READ from App: Button V0 - ON | LED: 🔴 ON
📤 WRITE to App: Temp: 26.5°C | Hum: 45.2%
📱 READ from App: Button V0 - OFF | LED: ⚪ OFF
```

### Blynk App Display

 Real-time temperature and humidity
 LED control button with status
 System status indicators

---

## 🐛 Troubleshooting

### Common Issues

1. Device Offline in Blynk

    Check WiFi credentials
    Verify Auth Token
    Ensure correct Blynk server configuration

2. Build Errors

    Clean project:

     ```bash
     pio run --target clean
     ```
    Check library dependencies in `platformio.ini`

3. Sensor Read Failures

    Verify DHT22 connections
    Check sensor initialization

### Simulation Notes

 Wokwi uses simulated sensor values (e.g., 79.9 °C, 40.0 %)
 Real hardware shows actual environmental data
 LED behavior is accurately simulated

---

## 📈 Future Enhancements

 [ ] Add multiple sensor support
 [ ] Implement data logging
 [ ] Add web dashboard
 [ ] Include alert notifications
 [ ] Support multiple ESP32 devices

---

## 🤝 Contributing

1. Fork the repository
2. Create feature branch:

   ```bash
   git checkout -b feature/new-feature
   ```
3. Commit changes:

   ```bash
   git commit -am "Add new feature"
   ```
4. Push to branch:

   ```bash
   git push origin feature/new-feature
   ```
5. Submit a pull request

---

## 🙏 Acknowledgments

 Blynk IoT Platform for cloud services
 Wokwi for ESP32 simulation environment
 PlatformIO for development tools
 Arduino Community for libraries and support

---

Developed for IoT Education and Demonstration
Perfect for academic projects and IoT learning 🎓

For questions or support, please open an issue in the repository.
