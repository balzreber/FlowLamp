/*
  ----------------------------------------------------------------------------
  Effect: Starfall
  Effect ID: starfall
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
   - mode (1 = rainbow, 2 = party, 3 = cloud, 4 = lave, 5 = forest) Color Palaette
  ----------------------------------------------------------------------------
*/

byte TWINKLES_SPEEDS = 4;     // only 4 blinking speed options
#define TWINKLES_MULTIPLIER 6 // too slow if at the slowest one just add one at a time
CRGB ledsbuff[NUM_LEDS];

byte twinklesHue = 0;

void effectTwinkles(int speed, int scale, int mode) {

  if(speed > 0 && speed < 50) TWINKLES_SPEEDS = 1;
  else if(speed > 51 && speed < 100) TWINKLES_SPEEDS = 2;
  else if(speed > 101 && speed < 150) TWINKLES_SPEEDS = 3;
  else if(speed > 151 && speed < 255) TWINKLES_SPEEDS = 4;

  if (mode == 1) cPalette = RainbowColors_p;
  else if (mode == 2) cPalette = PartyColors_p;
  else if (mode == 3) cPalette = CloudColors_p;
  else if (mode == 4) cPalette = LavaColors_p;
  else if (mode == 5) cPalette = ForestColors_p;
  else cPalette = PartyColors_p;

  if (loadingFlag)
  {
    loadingFlag = false;

    for (uint32_t idx = 0; idx < NUM_LEDS; idx++) {
      if (random8(scale % 11U) == 0) {
        ledsbuff[idx].r = random8();                          // оттенок пикселя
        ledsbuff[idx].g = random8(1, TWINKLES_SPEEDS * 2 + 1); // скорость и направление (нарастает 1-4 или угасает 5-8)
        ledsbuff[idx].b = random8();                          // яркость
      }
      else
        ledsbuff[idx] = 0;                                    // всё выкл
    }
  }


  for (uint32_t idx = 0; idx < NUM_LEDS; idx++) {
    if (ledsbuff[idx].b == 0) {
      if (random8(scale % 11U) == 0 && twinklesHue > 0) {  // если пиксель ещё не горит, зажигаем каждый ХЗй
        ledsbuff[idx].r = random8();                          // оттенок пикселя
        ledsbuff[idx].g = random8(1, TWINKLES_SPEEDS + 1);    // скорость и направление (нарастает 1-4, но не угасает 5-8)
        ledsbuff[idx].b = ledsbuff[idx].g;                    // яркость
        twinklesHue--; // уменьшаем количество погасших пикселей
      }
    }
    else if (ledsbuff[idx].g <= TWINKLES_SPEEDS) {            // если нарастание яркости
      if (ledsbuff[idx].b > 255U - ledsbuff[idx].g - TWINKLES_MULTIPLIER) {           // если досигнут максимум
        ledsbuff[idx].b = 255U;
        ledsbuff[idx].g = ledsbuff[idx].g + TWINKLES_SPEEDS;
      }
      else
        ledsbuff[idx].b = ledsbuff[idx].b + ledsbuff[idx].g + TWINKLES_MULTIPLIER;
    }
    else {                                                    // если угасание яркости
      if (ledsbuff[idx].b <= ledsbuff[idx].g - TWINKLES_SPEEDS + TWINKLES_MULTIPLIER) { // если досигнут минимум
        ledsbuff[idx].b = 0;                                  // всё выкл
        twinklesHue++; // считаем количество погасших пикселей
      }
      else
        ledsbuff[idx].b = ledsbuff[idx].b - ledsbuff[idx].g + TWINKLES_SPEEDS - TWINKLES_MULTIPLIER;
    }
    if (ledsbuff[idx].b == 0)
      leds[idx] = 0U;
    else
      leds[idx] = ColorFromPalette(cPalette, ledsbuff[idx].r, ledsbuff[idx].b);
  }
}
