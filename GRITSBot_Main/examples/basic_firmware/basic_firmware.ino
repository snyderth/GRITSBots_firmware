/* Define this variable to enable the compilation
   of the right I2C interface
 */
#define ESP8266

/* Include NeoPixel library for WS2812 LEDs */
#include <Adafruit_NeoPixel.h>

/* Include basic Arduino libraries */
#include <EEPROM.h>
#include <Arduino.h>
#include <Wire.h>

/* Include ESP8266 Wifi libraries */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/* Include JSON parser */
#include <ArduinoJson.h>

/*include OTA Libraries */
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

/* Include current sensor library */
#include <Adafruit_INA219.h>

/* Include GRITSBot header files */
#include "GRITSBot_Main_ESP8266.h"
#include "GRITSBot_Messages.h"

/* Include GRITSBot interface definitions for I2C */
#include "include/I2CMessage.h"
#include "I2CInterface.h"

/* Include GRITSBot interface definitions for WiFi and WiFi credentials*/
#include "wirelessInterfaceESP8266.h"
#include "wifiConfig.h"

/* Include estimator and controller libraries */
#include "include/controller/controllerBase.h"
#include "include/controller/controllerTarget.h"
#include "include/estimator/estimatorBase.h"

/* Instantiate Wifi UDP client */
WirelessInterfaceESP8266 wifi;

/* Instantiate I2C client */
I2CInterface i2c;

/* Instantiate currenet sensor */
Adafruit_INA219 ina219;

/* Instantiate controller and estimator */
ControllerTarget controller;
EstimatorBase estimator;

/* Instantiate WS2812 RGB LED strip */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, LED_PIN, NEO_GRB + NEO_KHZ800);

/* Instantiate main board */
GRITSBotMain mainboard(&wifi, &i2c, &ina219, &strip, &controller, &estimator);

bool forward = true;
long directionTime;
bool velSet = false;

/* **********************
 *     SETUP FUNCTION
 * **********************/
void setup() {
  directionTime = millis();
  Serial.begin(115200);
  Serial.println("Main board started");

  /* Initialize boards */
  mainboard.initialize();

  /* REMOVE: Disable motor voltage for testing */
  mainboard.enableMotorVoltage();

  /* Initializing OTA */
  ArduinoOTA.begin();
  Serial.println("Ready for OTA firmware updates");
  Serial.println("Main board initialized");
  Serial.print("Version Firmware Main : "); Serial.println(mainboard.getMainBoardFirmwareVersion());
  Serial.print("Version Hardware Main : "); Serial.println(mainboard.getMainBoardHardwareVersion());
  Serial.print("Version Firmware Motor: "); Serial.println(mainboard.getMotorBoardFirmwareVersion());
  Serial.print("Version Hardware Motor: "); Serial.println(mainboard.getMotorBoardHardwareVersion());

  /* Rainbow RGB LED animation */
  mainboard.rainbow(10);
  // mainboard.disableLedsRGB();
}

/* ********************
 *     MAIN LOOP
 * ********************/
void loop() {
  /* Update wireless function takes care of all message processing
   * and sends out heartbeat message every second
   */
   if(forward && !velSet)
     mainboard.setVelocities(0.2,0.2);
   else if(!forward && !velSet)
     mainboard.setVelocities(-0.2,-0.2);

   if((millis() - directionTime) > 10000){
     directionTime = millis();
     forward = !forward;
     velSet = false;
     Serial.println("Changing direction");
   }


  yield();
  mainboard.updateWireless();

  /* Update controller */
  yield();
  mainboard.updateController();

  /* Update measurement and data collection */
  yield();
  mainboard.updateMeasurements();

  /*OTA handling*/
  ArduinoOTA.handle();
}
