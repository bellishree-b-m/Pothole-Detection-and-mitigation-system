# Pothole-Detection-and-mitigation-system
To design a pothole detection system using sensors to identify potential road potholes and other anomalies.

## Overview
The Pothole Detection and Mitigation System is an IoT-based solution designed to improve road safety by detecting road anomalies such as potholes, speed humps, and uneven road surfaces. The system uses multiple sensors to identify anomalies, records their GPS location, and captures images using an ESP32-CAM module for further analysis.
The captured images can be annotated using Roboflow and utilized in a YOLOv8-based computer vision pipeline to support automated pothole detection and infrastructure monitoring.

## Features
- Detects potholes, speed humps, and uneven road surfaces
- GPS-based location tracking and alert generation
- Automatic image capture using ESP32-CAM and storage.
- Supports dataset preparation for computer vision applications

## Hardware Components
- Arduino UNO
- ESP32-CAM
- ADXL345 Accelerometer
- Ultrasonic Sensor (HC-SR04)
- GPS Module
- GSM(SIM800L)
- LCD Display

## Software & Tools
- Arduino IDE
- Roboflow
- Google Colab
- Python

## Outcome
The project demonstrates an integrated IoT solution for real-time road anomaly detection and reporting. By combining sensor-based detection with computer vision dataset preparation, the system supports smarter road infrastructure monitoring and contributes toward improved road safety and preventive maintenance.

