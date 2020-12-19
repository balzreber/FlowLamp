/*
  ----------------------------------------------------------------------------
  Effect: Color Change
  Effect ID: colorChange
  Exposes:
   - speed (0-255) ms Effect Timer
  ----------------------------------------------------------------------------
*/

byte colorChangeHue = 0;

void effectColorChange(int speed) {
  cPalette = RainbowColors_p;
  
  EVERY_N_MILLIS_I(effectTimer, speed) {
    colorChangeHue++;
  }
  effectTimer.setPeriod(speed);
  
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      drawPixelXY(x, y, ColorFromPalette(cPalette, colorChangeHue));
    }
  }
}
