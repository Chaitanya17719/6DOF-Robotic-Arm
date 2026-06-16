# 6-DOF Robotic Arm with Multi-Interface Control

## Overview

This project is a 6-DOF robotic arm designed and developed using ESP32-S3 and servo motors for precise joint control and pick-and-place operations. The system supports multiple control interfaces including joystick, web application, and mobile application, providing flexible and real-time operation.

The project demonstrates embedded systems, robotics, hardware-software integration, and motion control principles.

---

## Features

* 6 Degrees of Freedom (6-DOF)
* ESP32-S3 based control system
* Real-time servo coordination
* Multi-interface control

  * Joystick control
  * Web application control
  * Mobile application control
* Pick-and-place functionality
* Modular gripper design
* Smooth and accurate motion control

---

## Hardware Components

### Controller

* ESP32-S3

### Actuators

* MG995 Servo Motors
* MG90S Servo Motors

### Mechanical Components

* Custom robotic arm structure
* Modular gripper
* Servo brackets and linkages

### Power

* External power supply

---

## Software Stack

* Arduino IDE
* C/C++
* ESP32 Libraries
* Web Interface
* Mobile Application

---

## System Architecture

```text
            Web App
                |
                |
Joystick ---- ESP32-S3 ---- Mobile App
                |
                |
          Servo Motors
                |
                |
          6-DOF Robotic Arm
```

---

## Functionality

* Joint angle control
* Real-time movement
* Object gripping
* Pick-and-place operations
* Multi-platform operation
* Motion optimization

---

## Images

### Complete Robot

(Add image here)

### Side View

(Add image here)

### Gripper Mechanism

(Add image here)

### Web Application

(Add image here)

---

## Demonstration Videos

### Pick and Place Demo

(Add video link)

### Web Control Demo

(Add video link)

### Mobile App Control Demo

(Add video link)

---

## Future Improvements

* Computer vision integration using OpenCV
* Object detection using YOLOv8
* Autonomous pick-and-place operations
* Inverse kinematics implementation
* Modular end effectors
* AI-assisted control

---

## Repository Structure

```text
6DOF-Robotic-Arm/
│
├── README.md
├── images/
│   ├── front_view.jpg
│   ├── side_view.jpg
│   ├── gripper.jpg
│   └── web_interface.jpg
│
├── videos/
│   ├── pick_place_demo.mp4
│   ├── web_control_demo.mp4
│   └── mobile_control_demo.mp4
│
├── code/
│   ├── esp32_firmware/
│   ├── web_app/
│   └── mobile_app/
│
└── docs/
    └── circuit_diagram.png
```

---

## Applications

* Educational robotics
* Pick-and-place operations
* Embedded systems learning
* Motion control experiments
* Industrial automation concepts

---

## Author

**Chaitanya Sanikommu**

Electronics and Communication Engineering Undergraduate

Interests:

* Robotics
* Embedded Systems
* Computer Vision
* AI and Machine Learning
* Hardware-Software Integration
