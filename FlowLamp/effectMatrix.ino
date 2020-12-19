/*
  ----------------------------------------------------------------------------
  Effect: Matrix
  Effect ID: matrix
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/

void effectMatrix(int speed, int scale) {

  EVERY_N_MILLIS_I(effectTimer, speed) {

    for (byte x = 0; x < WIDTH; x++) {
      uint32_t thisColor = getPixColorXY(x, HEIGHT - 1);
      if (thisColor == 0)
        drawPixelXY(x, HEIGHT - 1, 0x00FF00 * (random(0, scale) == 0));
      else if (thisColor < 0x002000)
        drawPixelXY(x, HEIGHT - 1, 0);
      else
        drawPixelXY(x, HEIGHT - 1, thisColor - 0x002000);
    }

    for (byte x = 0; x < WIDTH; x++) {
      for (byte y = 0; y < HEIGHT - 1; y++) {
        drawPixelXY(x, y, getPixColorXY(x, y + 1));
      }
    }

  }
  effectTimer.setPeriod(speed);
}
