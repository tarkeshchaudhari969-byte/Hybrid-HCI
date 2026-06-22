
# GestureFusion

### Hybrid Wearable Gesture-Controlled Human-Computer Interaction System

GestureFusion is an open-source Hybrid Human-Computer Interaction (HCI) system that combines a wearable motion-sensing Air Mouse with AI-powered vision-based hand gesture recognition. The project enables intuitive, wireless, and contactless interaction with computers by integrating embedded systems, computer vision, and machine learning.

Unlike traditional input devices, GestureFusion allows users to control a computer using natural hand movements and gestures without relying on a conventional mouse.

---

## Features

### Motion-Sensing Air Mouse (ESP32 + MPU6050)

* Wireless Bluetooth HID Mouse
* Real-time cursor movement
* Motion sensing using MPU6050
* Cursor smoothing and vibration filtering
* Dead-zone implementation
* Adjustable sensitivity
* Mouse Left Click
* Mouse Right Click
* Portable wearable glove

### Vision-Based Gesture Recognition

* Real-time hand tracking using MediaPipe
* Gesture recognition using OpenCV
* Scrolling Control
* Volume Control
* Tab Switching
* Screenshot Capture
* Copy (Ctrl + C)
* Paste (Ctrl + V)
* Contactless computer interaction

---

## System Architecture

GestureFusion consists of two independent modules working together.

### 1. Motion-Sensing Air Mouse

Hardware:

* ESP32
* MPU6050 IMU
* Push Buttons
* Bluetooth BLE HID

Function:

* Detects hand orientation and motion.
* Converts sensor data into smooth cursor movement.
* Sends mouse events wirelessly using Bluetooth HID.

---

### 2. Vision-Based Gesture Recognition

Software:

* Python
* OpenCV
* MediaPipe Hands
* PyAutoGUI
* Keyboard Library

Function:

* Detects 21 hand landmarks.
* Recognizes predefined static and dynamic gestures.
* Executes system commands such as scrolling, screenshots, copy/paste, and volume control.

---

## Technologies Used

### Hardware

* ESP32
* MPU6050
* Bluetooth Low Energy (BLE)

### Software

* Python 3.9+
* C++
* PlatformIO
* OpenCV
* MediaPipe
* PyAutoGUI
* Keyboard Library
* NumPy

---

## Project Structure

```
Hybrid-HCI
│
├── ESP32-AirMouse
│   ├── src
│   ├── include
│   ├── lib
│   └── platformio.ini
│
├── Gesture-Recognition
│   ├── src
│   ├── requirements.txt
│   └── README.md
│
├── README.md
└── LICENSE
```

---

## Installation

### ESP32 Air Mouse

1. Open the firmware using PlatformIO.
2. Install the required ESP32 libraries.
3. Upload the firmware to the ESP32.
4. Pair the ESP32 with your computer using Bluetooth.

### Vision-Based Gesture Recognition

Clone the repository:

```bash
git clone <repository-url>
```

Install the required Python packages:

```bash
pip install -r requirements.txt
```

Run the gesture recognition module:

```bash
python advanced_main.py
```

---

## Future Improvements

* Custom Gesture Training
* AI-Based Gesture Classification
* Air Drawing
* Virtual Keyboard
* Multi-Hand Collaboration
* AR/VR Integration
* Adaptive Gesture Learning
* Cross-Platform Support

---

## Applications

* Human-Computer Interaction
* Accessibility Solutions
* Smart Presentations
* Automation
* Education
* Robotics
* AR/VR Interfaces
* Smart Workspaces

---

## Acknowledgements

The vision-based gesture recognition module builds upon existing open-source MediaPipe and OpenCV gesture recognition projects. The original implementation has been studied, modified, and integrated into this Hybrid Human-Computer Interaction system with additional features, ESP32-based Air Mouse integration, custom gesture mappings, and architectural improvements.

---

## License

This project is released under the MIT License.


A Hybrid Human-Computer Interaction System consisting of two independent modules.

1. Motion-Sensing Air Mouse
   - ESP32
   - MPU6050
   - Bluetooth HID
   - Real-time cursor control

2. Vision-Based Gesture Recognition
   - Python
   - OpenCV
   - MediaPipe
   - PyAutoGUI
   - Keyboard Library
  
## Acknowledgements

The vision-based gesture recognition module is based on the open-source project
"Advanced-Hand-Gesture-Recognition" by DYBInh2k5.

Original Repository:
https://github.com/DYBInh2k5/Advanced-Hand-Gesture-Recognition

This project extends the original work by integrating it with an ESP32 + MPU6050 wearable Air Mouse system and introducing a hybrid Human-Computer Interaction architecture.
