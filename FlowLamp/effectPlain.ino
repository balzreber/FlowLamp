/*
  ----------------------------------------------------------------------------
  Effect: Plain
  Effect ID: plain
  Exposes:
   - hue (0-360) Color Hue
  ----------------------------------------------------------------------------
*/

void effectPlain(int hue) {
  
  CHSV color = CHSV(map(hue, 0U, 360U, 0U, 255U), 255, 255);
  
  for (byte j = 0; j < HEIGHT; j++) {
    for (byte i = 0; i < WIDTH; i++)
    
      drawPixelXY(i, j, color);
  }
  
}
