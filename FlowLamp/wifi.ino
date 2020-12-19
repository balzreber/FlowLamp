
void connectWifi() {
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.disconnect(true);
  delay(2000);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(HOSTNAME);
  
  WiFi.begin(WLAN_SSID, WLAN_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  confirmMessage();
}

void printConnectionInfo() {

  Serial.println("");
  Serial.println("------------------------------------------------------------------------------");

  Serial.print("Host Name:");
  Serial.print("\t\t\t");
  Serial.println(HOSTNAME);

  Serial.print("MAC:");
  Serial.print("\t\t\t");
  Serial.println(WiFi.macAddress());

  Serial.print("IP:");
  Serial.print("\t\t\t");
  Serial.println(WiFi.localIP());

  Serial.print("Connected WiFi:");
  Serial.print("\t\t");
  Serial.println(WiFi.SSID());

  Serial.print("Connected MQTT Server:");
  Serial.print("\t");
  Serial.printf("%s:%d\n", MQTT_SERVER, MQTT_PORT);

  Serial.print("MQTT Toppic:");
  Serial.print("\t\t");
  Serial.println(MQTT_TOPIC);

  Serial.print("OTA HTTP Update Address:");
  Serial.print("\t");
  Serial.printf("http://%s:%d/update\n", WiFi.localIP().toString().c_str(), HTTP_UPDATE_PORT);

  Serial.println("------------------------------------------------------------------------------");
  Serial.println("");
  
}
