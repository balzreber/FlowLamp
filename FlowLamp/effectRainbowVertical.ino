/*
  ----------------------------------------------------------------------------
  Effect: Rainbow Horizontal
  Effect ID: rainbowHorizontal
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/

byte rainbowVertHue = 0;

void effectRainbowVertical(int speed, int scale) {

  EVERY_N_MILLIS_I(effectTimer, speed) {
    rainbowVertHue += 3;
  }
  effectTimer.setPeriod(speed);

  for (byte j = 0; j < HEIGHT; j++) {
    CHSV color = CHSV((byte)(rainbowVertHue + j * scale), 255, 255);
    for (byte i = 0; i < WIDTH; i++)
      drawPixelXY(i, j, color);
  }
}
