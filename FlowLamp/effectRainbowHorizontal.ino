/*
  ----------------------------------------------------------------------------
  Effect: Rainbow Horizontal
  Effect ID: rainbowHorizontal
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/

byte rainbowHorizHue = 0;

void effectRainbowHorizontal(int speed, int scale) {

  EVERY_N_MILLIS_I(effectTimer, speed) {
    rainbowHorizHue += 3;
  }
  effectTimer.setPeriod(speed);
  
  for (byte i = 0; i < WIDTH; i++) {
    CHSV color = CHSV((byte)(rainbowHorizHue + i * scale), 255, 255);
    for (byte j = 0; j < HEIGHT; j++)
      drawPixelXY(i, j, color);
  }
}
