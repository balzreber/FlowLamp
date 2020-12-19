/*
  ----------------------------------------------------------------------------
  Effect: Snow
  Effect ID: snow
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/

void effectSnow(int speed, int scale) {

  EVERY_N_MILLIS_I(effectTimer, speed) {

    for (byte x = 0; x < WIDTH; x++) {
      for (byte y = 0; y < HEIGHT - 1; y++) {
        drawPixelXY(x, y, getPixColorXY(x, y + 1));
      }
    }

    for (byte x = 0; x < WIDTH; x++) {
      if (getPixColorXY(x, HEIGHT - 2) == 0 && (random(0, scale) == 0))
        drawPixelXY(x, HEIGHT - 1, 0xE0FFFF - 0x101010 * random(0, 4));
      else
        drawPixelXY(x, HEIGHT - 1, 0x000000);
    }

  }
  effectTimer.setPeriod(speed);
}
