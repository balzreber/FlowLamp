 /*
  ----------------------------------------------------------------------------
  Copyright (C) Globo-Bruell Heavy Industry Systems, Ltd - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential part of the bHive Project.
  For more information see LICENSE file, included in this project.
  Written 2018 by Balz Reber <balz.reber@globobruell.com>
  ----------------------------------------------------------------------------
*/


/*--------------------------*/
/* LIBRARY INCLUDES         */
/*--------------------------*/

// Wifi Library
#include <ESP8266WiFi.h>

// OTA Libraries
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

// MQTT Library
#include <PubSubClient.h>

// LED Library
#include <FastLED.h>

// Capacitive Button
#include <GyverButton.h>

/*--------------------------*/
/* VAR DECLARATIONS         */
/*--------------------------*/

/* CONSTANTS */

#define HOSTNAME          "FlowLamp-01"

#define WLAN_SSID         "bHive_IoT"
#define WLAN_PW           "LN+GzEBDyjvW9x=P"

#define MQTT_SERVER       "192.168.1.10"
#define MQTT_PORT         1883
#define MQTT_TOPIC        "bHive/FlowLamp-01"

const char channel_0[] = "effect";
const char channel_1[] = "brightness";
const char channel_2[] = "hue";
const char channel_3[] = "speed";
const char channel_4[] = "scale";
const char channel_5[] = "mode";

const char *MQTT_CHANNELS[] = {
  channel_0,
  channel_1,
  channel_2,
  channel_3,
  channel_4,
  channel_5 
};


#define HTTP_UPDATE_PORT  9090

#define PIN_LED           1
#define PIN_BUTTON        0

#define BRIGHTNESS        40                // standard?? maximum?? brightness (0-255)
#define CURRENT_LIMIT     2000              // current limit in milliamperes, automatically controls brightness (spare your power supply!) 0 - turn off the limit

#define WIDTH             16                // LED Matrix width
#define HEIGHT            16                // Led Matrix height
#define NUM_LEDS          WIDTH * HEIGHT




#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_ESP8266_RAW_PIN_ORDER



/* VARS */


boolean powerState = false;


int currentEffect = 0;


struct {
  byte brightness = 50;
  byte hue = 0;
  byte speed = 30;
  byte scale = 99;
  byte mode = 0;
} effectSettings[18];


boolean loadingFlag = true;






/*--------------------------*/
/* LIBRARY INSTANTIATIONS   */
/*--------------------------*/

ESP8266WebServer httpServer(HTTP_UPDATE_PORT);
ESP8266HTTPUpdateServer httpUpdater;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

GButton touch(PIN_BUTTON, LOW_PULL, NORM_OPEN);

CRGB leds[NUM_LEDS];

CRGBPalette16 cPalette(PartyColors_p);

/*--------------------------*/
/* SETUP                    */
/*--------------------------*/

void setup() {
  
  Serial.begin(115200);
  Serial.println("");

  FastLED.addLeds<WS2812B, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  if(CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  FastLED.clear(true);

  //touch.setStepTimeout(100);
  //touch.setClickTimeout(500);

  connectWifi();
  printConnectionInfo();

  initOta();

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

}


/*--------------------------*/
/* LOOP                     */
/*--------------------------*/

void loop() {

  // Handle OTA Update
  httpServer.handleClient();

  if (!mqttClient.connected()) {
    mqttConnect();
  }
  mqttClient.loop();

  if(powerState) effectsTick();
  //buttonTick();

}
