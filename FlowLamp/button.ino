boolean brightDirection;

void buttonTick() {
  
  touch.tick();
  
  if(touch.isSingle()) {
    
    Serial.print("Single Click Detected ");
    Serial.println(powerState);
    
    if(powerState) setPowerState(false);
    else setPowerState(true);
  }

  if(touch.isDouble()) {
    Serial.println("Double Click Detected ");
  }

/*
  if (ONflag && touch.isDouble()) {
    demo = false;
    if (++currentMode >= MODE_AMOUNT) currentMode = 0;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    sendSettings_flag = true;
    MQTTUpdateState();
  }

if (ONflag && touch.isTriple()) {
    demo = false;
    if (--currentMode < 0) currentMode = MODE_AMOUNT - 1;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    MQTTUpdateState();
    sendSettings_flag = true;
  }

 // вывод IP на лампу
  if (ONflag && touch.hasClicks()) {
    if (touch.getClicks() == 5) {
      resetString();
      while (!fillString(WiFi.localIP().toString(), CRGB::Green, true)) {
        delay(1);
        yield();
      }
    }
  }

  if (ONflag && touch.isHolded()) {
    brightDirection = !brightDirection;
  }
  
  if (ONflag && touch.isStep()) {
    if (brightDirection) {
      if (modes[currentMode].brightness < 10) modes[currentMode].brightness += 1;
      else if (modes[currentMode].brightness < 250) modes[currentMode].brightness += 5;
      else modes[currentMode].brightness = 255;
    } else {
      if (modes[currentMode].brightness > 15) modes[currentMode].brightness -= 5;
      else if (modes[currentMode].brightness > 1) modes[currentMode].brightness -= 1;
      else modes[currentMode].brightness = 1;
    }
    FastLED.setBrightness(modes[currentMode].brightness);
    settChanged = true;
    eepromTimer = millis();
    sendSettings_flag = true;
    MQTTUpdateState();
  }
  */
  
}
