/*
  ----------------------------------------------------------------------------
  Effect: Fireflies
  Effect ID: fireflies
  Exposes:
   - speed (0-255) ms Effect Timer
  ----------------------------------------------------------------------------
*/


#define LIGHTERS_AM 100
int lightersPos[2][LIGHTERS_AM];
int8_t lightersSpeed[2][LIGHTERS_AM];
CHSV lightersColor[LIGHTERS_AM];
byte loopCounter;

int angle[LIGHTERS_AM];
int speedV[LIGHTERS_AM];
int8_t angleSpeed[LIGHTERS_AM];

void effectFireflies(int speed) {

  EVERY_N_MILLIS_I(effectTimer, speed) {

    FastLED.clear();
    if (++loopCounter > 20) loopCounter = 0;
    for (byte i = 0; i < effectSettings[11].scale; i++) {
      if (loopCounter == 0) {     // меняем скорость каждые 255 отрисовок
        lightersSpeed[0][i] += random(-3, 4);
        lightersSpeed[1][i] += random(-3, 4);
        lightersSpeed[0][i] = constrain(lightersSpeed[0][i], -20, 20);
        lightersSpeed[1][i] = constrain(lightersSpeed[1][i], -20, 20);
      }

      lightersPos[0][i] += lightersSpeed[0][i];
      lightersPos[1][i] += lightersSpeed[1][i];

      if (lightersPos[0][i] < 0) lightersPos[0][i] = (WIDTH - 1) * 10;
      if (lightersPos[0][i] >= WIDTH * 10) lightersPos[0][i] = 0;

      if (lightersPos[1][i] < 0) {
        lightersPos[1][i] = 0;
        lightersSpeed[1][i] = -lightersSpeed[1][i];
      }
      if (lightersPos[1][i] >= (HEIGHT - 1) * 10) {
        lightersPos[1][i] = (HEIGHT - 1) * 10;
        lightersSpeed[1][i] = -lightersSpeed[1][i];
      }
      drawPixelXY(lightersPos[0][i] / 10, lightersPos[1][i] / 10, lightersColor[i]);
    }

  }
  effectTimer.setPeriod(speed);

}
