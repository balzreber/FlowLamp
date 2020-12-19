/*
  ----------------------------------------------------------------------------
  Effect: Starfall
  Effect ID: starfall
  Exposes:
   - speed (0-255) ms Effect Timer
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/

#define STAR_DENSE            (60U)                         // плотность комет
#define STAR_TAIL_STEP        (100U)                        // длина хвоста кометы
#define STAR_SATURATION       (200U)                        // насыщенность кометы (от 0 до 255)

void effectStarfall(int speed, int scale)
{

  EVERY_N_MILLIS_I(effectTimer, speed) {
 
    for (uint8_t i = 0U; i < WIDTH; i++)
    {
      if (getPixColorXY(i, HEIGHT - 1U) == 0U &&
         (random(0, map(scale, 0U, 255U, 10U, 120U)) == 0U) &&
          getPixColorXY(i + 1U, HEIGHT - 1U) == 0U &&
          getPixColorXY(i - 1U, HEIGHT - 1U) == 0U)
      {
        leds[getPixelNumber(i, HEIGHT - 1U)] = CHSV(random(0, 200), STAR_SATURATION, 255U);
      }
    }
  
    // сдвигаем по диагонали
    for (uint8_t y = 0U; y < HEIGHT - 1U; y++)
    {
      for (uint8_t x = WIDTH - 1U; x > 0U; x--)
      {
        drawPixelXY(x, y, getPixColorXY(x - 1U, y + 1U));
      }
      drawPixelXY(0, y, getPixColorXY(WIDTH - 1U, y + 1U));
    }
  
    for (uint8_t i = 0U; i < WIDTH; i++)
    {
      fadePixel(i, HEIGHT - 1U, STAR_TAIL_STEP);
    }

  }
  effectTimer.setPeriod(speed);
}
