/*
  ----------------------------------------------------------------------------
  Effect: Plain Faded
  Effect ID: plainFaded
  Exposes:
   - hue (0-360) Color Hue
   - scale (0-x??) Effect Scale
  ----------------------------------------------------------------------------
*/


void effectPlainFaded(int hue, int scale)
{
  uint8_t centerY = max((uint8_t)round(HEIGHT / 2.0F) - 1, 0);
  uint8_t bottomOffset = (uint8_t)(!(HEIGHT & 1) && (HEIGHT > 1));

  if (scale<17) scale = 17;
  for (int16_t y = centerY; y >= 0; y--)
  {
    CRGB color = CHSV(map(hue, 0U, 360U, 0U, 255U), 255,
      y == centerY
      ? 255U
      : (scale / 100.0F) > ((centerY + 1.0F) - (y + 1.0F)) / (centerY + 1.0F) ? 255U : 0U);

    for (uint8_t x = 0U; x < WIDTH; x++)
    {
      drawPixelXY(x, y, color);
      drawPixelXY(x, max((uint8_t)(HEIGHT - 1U) - (y + 1U) + bottomOffset, 0U), color);
    }
  }
}
