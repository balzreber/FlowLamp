
void mqttConnect() {

  while (!mqttClient.connected()) {

    // Create a random client ID
    String clientId = HOSTNAME;
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {

      for(int i = 0; i < sizeof(MQTT_CHANNELS) / sizeof(MQTT_CHANNELS[0]); i++) {
        Serial.println((String(MQTT_TOPIC) + "/" + String(MQTT_CHANNELS[i])).c_str());
        mqttClient.subscribe((String(MQTT_TOPIC) + "/" + String(MQTT_CHANNELS[i])).c_str()); 
      }
      mqttSendConnectionInfo();

    } else {

      Serial.print("MQTT Disconnect");
      Serial.print(mqttClient.state());
      delay(100);

    }
  }
}


void mqttSendConnectionInfo() {
  
  mqttPublish(String(MQTT_TOPIC) + "/hostname", HOSTNAME);
  mqttPublish(String(MQTT_TOPIC) + "/mac", WiFi.macAddress());
  mqttPublish(String(MQTT_TOPIC) + "/ip", WiFi.localIP().toString());
  mqttPublish(String(MQTT_TOPIC) + "/connectedWifi", WiFi.SSID());
  mqttPublish(String(MQTT_TOPIC) + "/connectedMqtt", String(MQTT_SERVER) + ":" + String(MQTT_PORT));
  mqttPublish(String(MQTT_TOPIC) + "/mqttTopic", MQTT_TOPIC);
  mqttPublish(String(MQTT_TOPIC) + "/otaAddress", "http://" + WiFi.localIP().toString() + ":" + String(HTTP_UPDATE_PORT) + "/update");
}


void mqttPublish(char* topic, char* payload) {

  mqttClient.publish(topic, payload);
}


void mqttPublish(String topic, String payload) {
  
  const char *topicChar = topic.c_str();
  const char *payloadChar = payload.c_str();
  
  mqttClient.publish(topicChar, payloadChar);
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  
  String fullPayload;
  for (int i = 0; i < length; i++) {
    fullPayload += (char)payload[i];
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/effect").c_str()) == 0) {
    if(fullPayload != "off") setPowerState(true);
    currentEffect = getEffectId(fullPayload);
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/brightness").c_str()) == 0) {
    effectSettings[currentEffect].brightness = fullPayload.toInt();
    FastLED.setBrightness(effectSettings[currentEffect].brightness);
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/hue").c_str()) == 0) {
    effectSettings[currentEffect].hue = fullPayload.toInt();
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/speed").c_str()) == 0) {
    effectSettings[currentEffect].speed = fullPayload.toInt();
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/scale").c_str()) == 0) {
    effectSettings[currentEffect].scale = fullPayload.toInt();
  }

  if(strcmp(topic, (String(MQTT_TOPIC) + "/mode").c_str()) == 0) {
    effectSettings[currentEffect].mode = fullPayload.toInt();
  }

}
