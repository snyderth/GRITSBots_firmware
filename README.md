# GRITSBots_firmware

Firmware for UGVs in the Oregon State HMT lab

## Getting Started

Copy this repo into the libraries folder of your arduino installation. Also add 
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
to File>preferences>Additional Boards Manager URLs field in you arduino IDE to get the esp boards that are used.

## Flashing the mainboard

For OTA capable updates, flash using the board NodeMCU 1.0 (12E). Also make sure that the wifi SSID and broadcast IP (IP of computer that will send and receive messages to and from UGVs) is set correctly in WIFIConfig.h.

## OTA Update Using HTTP server

The code for this is on line 629 of GRITSBot_Main_ESP8266.cpp. Make sure that IP points to the http server on the network and that there is a file named 
```
newfirmware.bin
```
or whatever you like on that server.
