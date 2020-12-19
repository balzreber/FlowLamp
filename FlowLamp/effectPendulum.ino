/*
  ----------------------------------------------------------------------------
  Effect: Pendulum
  Effect ID: pendulum
  Exposes:
   - speed (0-255) ms Effect Timer
   - mode (1 = rainbow, 2 = party, 3 = cloud, 4 = lave, 5 = forest) Color Palaette
  ----------------------------------------------------------------------------
*/

byte pendulumHue = 0;

void effectPendulum(int speed, int mode) {

  EVERY_N_MILLIS_I(effectTimer, speed) {
    pendulumHue++;
  }
  effectTimer.setPeriod(speed);

  FastLED.clear();

  if (mode == 1) cPalette = RainbowColors_p;
  else if (mode == 2) cPalette = PartyColors_p;
  else if (mode == 3) cPalette = CloudColors_p;
  else if (mode == 4) cPalette = LavaColors_p;
  else if (mode == 5) cPalette = ForestColors_p;
  else cPalette = PartyColors_p;

  for (int x = 0; x < WIDTH; x++)
  {
    uint8_t beat = (GET_MILLIS() * (accum88(x + 1)) * 28 * effectSettings[8].speed) >> 17;
    uint8_t y = scale8(sin8(beat), HEIGHT - 1);
    drawPixelXY(x, y, ColorFromPalette(cPalette , x * 7 + pendulumHue));
  }
}
