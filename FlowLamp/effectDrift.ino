/*
  ----------------------------------------------------------------------------
  Effect: Drift
  Effect ID: drift
  Exposes:
   - speed (0-255) ms Effect Timer
   - mode (1 = rainbow, 2 = party, 3 = cloud, 4 = lave, 5 = forest) Color Palaette
  ----------------------------------------------------------------------------
*/

void effectDrift(int speed, int mode) {

  EVERY_N_MILLIS_I(effectTimer, speed) {


    const int CENTER_X = WIDTH / 2;
    const int CENTER_Y = HEIGHT / 2;

    if (mode == 1) cPalette = RainbowColors_p;
    else if (mode == 2) cPalette = PartyColors_p;
    else if (mode == 3) cPalette = CloudColors_p;
    else if (mode == 4) cPalette = LavaColors_p;
    else if (mode == 5) cPalette = ForestColors_p;
    else cPalette = PartyColors_p;

    uint8_t dim = beatsin8(2, 170, 250);
    dimAll(dim);

    for (uint8_t i = 0; i < WIDTH; i++)
    {
      CRGB color;
      uint8_t x = 0;
      uint8_t y = 0;

      if (i < CENTER_X) {
        x = beatsin8((i + 1) * 2, i, WIDTH - i, 0, 180);
        y = beatsin8((i + 1) * 2, i, HEIGHT - i);
        color = ColorFromPalette(cPalette , i * 14);
      }
      else
      {
        x = beatsin8((WIDTH  - i) * 2, WIDTH - i, i + 1);
        y = beatsin8((HEIGHT - i) * 2, HEIGHT - i, i + 1, 0, 180);
        color = ColorFromPalette(cPalette , (31 - i) * 14);
      }
      drawPixelXY(x, y, color);
    }

  }
  effectTimer.setPeriod(speed);
}
