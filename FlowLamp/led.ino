
#define SEGMENTS 1            // diodes in one "pixel" (to create a matrix from pieces of tape)

void drawPixelXY(int8_t x, int8_t y, CRGB color) {
  if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1) return;
  int thisPixel = getPixelNumber(x, y) * SEGMENTS;
  for (byte i = 0; i < SEGMENTS; i++) {
    leds[thisPixel + i] = color;
  }
}


uint16_t getPixelNumber(int8_t x, int8_t y) {

  int _WIDTH = WIDTH;
  int THIS_X = (WIDTH - x - 1);
  int THIS_Y = (HEIGHT - y - 1);

  if (THIS_Y % 2 == 0) {
    return (THIS_Y * _WIDTH + THIS_X);
  } else {
    return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
  }
}


uint32_t getPixColorXY(int8_t x, int8_t y) {
  return getPixColor(getPixelNumber(x, y));
}


uint32_t getPixColor(int thisSegm) {
  int thisPixel = thisSegm * SEGMENTS;
  if (thisPixel < 0 || thisPixel > NUM_LEDS - 1) return 0;
  return (((uint32_t)leds[thisPixel].r << 16) | ((long)leds[thisPixel].g << 8 ) | (long)leds[thisPixel].b);
}


void fadePixel(byte i, byte j, byte step) {     // новый фейдер
  int pixelNum = getPixelNumber(i, j);
  if (getPixColor(pixelNum) == 0) return;

  if (leds[pixelNum].r >= 30 ||
      leds[pixelNum].g >= 30 ||
      leds[pixelNum].b >= 30) {
    leds[pixelNum].fadeToBlackBy(step);
  } else {
    leds[pixelNum] = 0;
  }
}


void dimAll(uint8_t value) {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(value); //fadeToBlackBy
  }
}


void fadeToBlack() {

  /*

  int fadeStart = FastLED.getBrightness();
  int fade = fadeStart;

  while (1) {
    EVERY_N_MILLIS(10) {

      if (fade == 0) break;

      FastLED.setBrightness(fade);

      fade--;
    }
  }

  Serial.println("FADE HAS ENDED");
*/
}


void confirmMessage() {
  FastLED.clear();

  int lines[HEIGHT];
  int steps = 0;
  int xPos = 0;
  //int steps = WIDTH * 2;

  /*
    EVERY_N_MILLIS(100) {

      for(byte i = 0; i < HEIGHT; i++) {
        for(byte j = 0; j < WIDTH; j++) {

          if(xPos == j && )

          drawPixelXY(i, cnter, color);
        }
      }
      steps++;
    }
  */

  int cntr = 0;
  for (byte i = 0; i < WIDTH; i++) {
    CHSV color = CHSV(map(i, 0, WIDTH, 0, 255), 255, 255);
    drawPixelXY(i, cntr, color);
    cntr++;
  }
  FastLED.show();

  delay(2000);
  FastLED.clear(true);
}
