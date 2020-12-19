/*
  ----------------------------------------------------------------------------
  Effect: Matrix
  Effect ID: matrix
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
   - mode (1 = madness, 2 = rainbow, 3 = rainbowStripe, 4 = zebra, 5 = forest, 6 = ocean, 7 = plasma, 8 = cloud, 9 = lava) Color Palaette
  ----------------------------------------------------------------------------
*/

// The 16 bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

uint16_t iSpeed = 20; // speed is set dynamically once we've started up
uint16_t iScale = 30; // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
#define MAX_DIMENSION (max(WIDTH, HEIGHT))
#if (WIDTH > HEIGHT)
uint8_t noise[WIDTH][WIDTH];
#else
uint8_t noise[HEIGHT][HEIGHT];
#endif

CRGBPalette16 currentPalette( PartyColors_p );
uint8_t colorLoop = 1;
uint8_t ihue = 0;

void effectNoise(int speed, int scale, int mode) {

  iSpeed = speed;
  iScale = scale;

  switch (mode) {
    case 1: madnessNoise();
      break;
    case 2: rainbowNoise();
      break;
    case 3: rainbowStripeNoise();
      break;
    case 4: zebraNoise();
      break;
    case 5: forestNoise();
      break;
    case 6: oceanNoise();
      break;
    case 7: plasmaNoise();
      break;
    case 8: cloudNoise();
      break;
    case 9: lavaNoise();
      break;
    default: madnessNoise();
      break;

  }
}


void madnessNoise() {
  fillnoise8();
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      CRGB thisColor = CHSV(noise[j][i], 255, noise[i][j]);
      drawPixelXY(i, j, thisColor);   //leds[getPixelNumber(i, j)] = CHSV(noise[j][i], 255, noise[i][j]);
    }
  }
  ihue += 1;
}

void rainbowNoise() {
  currentPalette = RainbowColors_p;
  colorLoop = 1;
  fillNoiseLED();
}

void rainbowStripeNoise() {
  currentPalette = RainbowStripeColors_p;
  colorLoop = 1;
  fillNoiseLED();
}

void zebraNoise() {
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
  colorLoop = 1;
  fillNoiseLED();
}

void forestNoise() {
  currentPalette = ForestColors_p;
  colorLoop = 0;
  fillNoiseLED();
}
void oceanNoise() {
  currentPalette = OceanColors_p;
  colorLoop = 0;
  fillNoiseLED();
}

void plasmaNoise() {
  currentPalette = PartyColors_p;
  colorLoop = 1;
  fillNoiseLED();
}

void cloudNoise() {
  currentPalette = CloudColors_p;
  colorLoop = 0;
  fillNoiseLED();
}

void lavaNoise() {
  currentPalette = LavaColors_p;
  colorLoop = 0;
  fillNoiseLED();
}


void fillNoiseLED() {
  uint8_t dataSmoothing = 0;
  if ( iSpeed < 50) {
    dataSmoothing = 200 - (iSpeed * 4);
  }
  for (int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = iScale * i;
    for (int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = iScale * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);

      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if ( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }
  z += iSpeed;

  // apply slow drift to X and Y, just for visual variation.
  x += iSpeed / 8;
  y -= iSpeed / 16;

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];
      // if this palette is a 'loop', add a slowly-changing base value
      if ( colorLoop) {
        index += ihue;
      }
      // brighten up, as the color palette itself often contains the
      // light/dark dynamic range desired
      if ( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }
      CRGB color = ColorFromPalette( currentPalette, index, bri);
      drawPixelXY(i, j, color);   //leds[getPixelNumber(i, j)] = color;
    }
  }
  ihue += 1;
}

void fillnoise8() {
  for (int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = iScale * i;
    for (int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = iScale * j;
      noise[i][j] = inoise8(x + ioffset, y + joffset, z);
    }
  }
  z += iSpeed;
}
