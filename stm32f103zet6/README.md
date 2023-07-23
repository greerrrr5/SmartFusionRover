# Detection System

## Project Overview

This project utilizes STM32F103ZET6 and ESP8266WiFi to upload environmental parameter data to the OneNET cloud platform. It also includes functionality to display real-time data on an LCD.

## System Architecture

The system architecture of this project consists of the following components:

- STM32F103ZET6 development board
- ESP8266WiFi module
- Sensors for measuring environmental parameters
- OneNET cloud platform for data storage and retrieval
- LCD for displaying real-time data

## Features

- Collects environmental parameter data using sensors.
- Establishes a connection to the OneNET cloud platform via ESP8266WiFi.
- Uploads the collected data to the OneNET cloud platform.
- Displays real-time parameter data on an LCD.

## Hardware Requirements

To replicate this project, you will need the following hardware:

- STM32F103ZET6 development board
- ESP8266WiFi module
- Sensors compatible with STM32F103ZET6
- LCD display compatible with STM32F103ZET6

## Software Dependencies

This project relies on the following software dependencies:

- STM32CubeIDE (for programming the STM32F103ZET6 development board)
- Arduino IDE (for programming the ESP8266WiFi module)
- OneNET API (to enable communication with the OneNET cloud platform)

## Getting Started

To get started with this project, follow these steps:

1. Set up the STM32F103ZET6 development board and connect the sensors and LCD.
2. Import the project code into the STM32CubeIDE.
3. Configure the ESP8266WiFi module with the necessary settings in the code.
4. Program the STM32F103ZET6 development board with the code.
5. Connect the ESP8266WiFi module to your local network.
6. Establish a successful connection between the STM32F103ZET6 and OneNET platform.
7. Run the project and monitor the real-time data on the LCD display.

Copyright © 2023 by Greer Liu, Siying Wang, Yaping Mei, Tian Xu, Junyi Zhang, Chengyu Wu, Xinyue Wang, All rights reserved.