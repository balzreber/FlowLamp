
void setPowerState(bool pState) {
  if(pState) {
    powerState = true;
    currentEffect = 1;
  } else {
    powerState = false;
    //fadeToBlack();
    FastLED.clear(true);
  }
}


int getEffectId(String effect) {
  if (effect.equals("off")) return 0;
  if (effect.equals("plain")) return 1;
  if (effect.equals("plainFaded")) return 2;
  if (effect.equals("colorChange")) return 3;
  if (effect.equals("rainbowVertical")) return 4;
  if (effect.equals("rainbowHorizontal")) return 5;
  if (effect.equals("snow")) return 6;
  if (effect.equals("matrix")) return 7;
  if (effect.equals("pendulum")) return 8;
  if (effect.equals("twinkles")) return 9;
  if (effect.equals("starfall")) return 10;
  if (effect.equals("fireflies")) return 11;
  if (effect.equals("drift")) return 12;
  if (effect.equals("spiral")) return 13;
  if (effect.equals("pride")) return 14;
  if (effect.equals("noise")) return 15;
  if (effect.equals("fire")) return 16;
  if (effect.equals("alarm")) return 17;
  if (effect.equals("demo")) return 18;
}


void effectsTick() {

  switch (currentEffect) {
    case 0: setPowerState(false);
      break;
    case 1: effectPlain(effectSettings[1].hue);
      break;
    case 2: effectPlainFaded(effectSettings[2].hue, effectSettings[2].scale);
      break;
    case 3: effectColorChange(effectSettings[3].speed);
      break;
    case 4: effectRainbowVertical(effectSettings[4].speed, effectSettings[4].scale);
      break;
    case 5: effectRainbowHorizontal(effectSettings[5].speed, effectSettings[5].scale);
      break;
    case 6: effectSnow(effectSettings[6].speed, effectSettings[6].scale);
      break;
    case 7: effectMatrix(effectSettings[7].speed, effectSettings[7].scale);
      break;
    case 8: effectPendulum(effectSettings[8].speed, effectSettings[8].mode);
      break;
    case 9: effectTwinkles(effectSettings[9].speed, effectSettings[9].scale, effectSettings[9].mode);
      break;
    case 10: effectStarfall(effectSettings[10].speed, effectSettings[10].scale);
      break;
    case 11: effectFireflies(effectSettings[11].speed);
      break;
    case 12: effectDrift(effectSettings[12].speed, effectSettings[12].mode);
      break;
    case 13: effectSpiral();
      break;
    case 14: effectPride();
      break;
    case 15: effectNoise(effectSettings[15].speed, effectSettings[15].scale, effectSettings[15].mode);
      break;
    case 16: effectFire(effectSettings[16].hue, effectSettings[16].speed);
      break;
    case 17: effectAlarm(effectSettings[17].speed, effectSettings[17].mode);
      break;
    case 18: //demo();
      break;
  }
  
  FastLED.show();
}
