# NodeMCU ESP8266

## Project Overview

This project enables real-time data monitoring and voice announcements using NodeMCU ESP8266 with OneNET integration. The NodeMCU reads data from OneNET and triggers a speech announcement when the data reaches a threshold value. The parameter data is also displayed in real-time on a WeChat Mini Program.

## System Architecture

The system architecture of this project consists of the following components:

- NodeMCU ESP8266 development board
- Sensors compatible with NodeMCU
- OneNET platform for data storage and retrieval
- WeChat Mini Program for real-time data visualization

## Features

- Fetches sensor data from the OneNET platform.
- Monitors the data for threshold exceedance.
- Triggers a voice announcement when the threshold is reached.
- Displays real-time parameter data on a WeChat Mini Program.

## Hardware Requirements

To replicate this project, you will need the following hardware:

- NodeMCU ESP8266 development board
- Sensors compatible with NodeMCU
- Speaker or audio output device

## Software Dependencies

This project relies on the following software dependencies:

- Arduino IDE
- OneNET API (to enable communication with the OneNET platform)
- WeChat Mini Program development tool

## Getting Started

To get started with this project, follow these steps:

1. Set up the NodeMCU ESP8266 development board and connect the sensors.
2. Import the project code into the Arduino IDE.
3. Configure the OneNET API key and other necessary settings in the code.
4. Upload the code to the NodeMCU ESP8266 development board.
5. Run the WeChat Mini Program and establish a successful connection with the OneNET platform.

----
Copyright © 2023 by Greer Liu, Siying Wang, Yaping Mei, Tian Xu, Junyi Zhang, Chengyu Wu, Xinyue Wang, All rights reserved.
