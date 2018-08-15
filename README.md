# GRITSBots_firmware

Firmware for UGVs in the Oregon State HMT lab

## Getting Started

Copy this repo into the libraries folder of your arduino installation. Also add 
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
to File>preferences>Additional Boards Manager URLs field in you arduino IDE to get the esp boards that are used.

## Flashing the mainboard

For OTA capable updates, flash using the board NodeMCU 1.0 (12E). Also make sure that the wifi SSID and broadcast IP (IP of computer that will send and receive messages to and from UGVs) is set correctly in GRITSBot_WIFIConfig/WIFIConfig.h.

## OTA Update Using HTTP server

The code for this is on line 629 of GRITSBot_Main_ESP8266.cpp. Make sure that IP points to the http server on the network and that there is a file named 
```
newfirmware.bin
```
or whatever you like on that server.

## Arduino folder structure
```
Arduino
|_basic_firmware
|	|_basic_firmware.ino (seperately saved, unnecssary)
|_GRITSBOT_MESSAGES.py
|_sendGRITSmessagesUDP.py
|_udpMessages.py
|_upload_to_pi.sh (references the basic_firmware folder in this directory)
|_libraries (Arduino default library folder)
	|_Adafruit_INA219
	|_Adafruit_NeoPixel
	|_ArduinoJson
	|_GRITSBot_I2CInterface
	|_GRITSBot_Main
	|	|_GRITSBot_Main_ESP8266.cpp
	|	|_GRITSBot_Main_ESP8266.h
	|	|_examples
	|		|_basic_firmware (Contains original example, shows as example in Arduino IDE)
	|		|_random_walk
	|_GRITSBot_Messages
	|_GRITSBot_Motor
	|	|_examples
	|		|_basic_firmware(Contains original example, shows as example in Arduino IDE)
	|		|_random_walk
	|_GRITSBot_WiFiConfig
	|_GRITSBot_WirelessInterface
```
