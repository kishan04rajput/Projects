int counter = 0;
byte your_text[400][6] = {};
void character()
{
  while (inputMessage[counter] != '\0')
  {
    if (inputMessage[counter] == 'A' || inputMessage[counter] == 'a')
    {
      your_text[counter][0] = B01110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B11111000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'B' || inputMessage[counter] == 'b')
    {
      your_text[counter][0] = B11110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B11110000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == 'C' || inputMessage[counter] == 'c')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B10000000;
      your_text[counter][2] = B10000000;
      your_text[counter][3] = B10000000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == 'D' || inputMessage[counter] == 'd')
    {
      your_text[counter][0] = B11110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B10001000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B11110000;
    }
    if (inputMessage[counter] == 'E' || inputMessage[counter] == 'e')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B10000000;
      your_text[counter][2] = B10000000;
      your_text[counter][3] = B11110000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == 'F' || inputMessage[counter] == 'f')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B10000000;
      your_text[counter][2] = B10000000;
      your_text[counter][3] = B11110000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B10000000;
    }
    if (inputMessage[counter] == 'G' || inputMessage[counter] == 'g')
    {
      your_text[counter][0] = B01110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10000000;
      your_text[counter][3] = B10011000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B01110000;
    }
    if (inputMessage[counter] == 'H' || inputMessage[counter] == 'h')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B11111000;
      your_text[counter][3] = B10001000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'I' || inputMessage[counter] == 'i')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B00100000;
      your_text[counter][2] = B00100000;
      your_text[counter][3] = B00100000;
      your_text[counter][4] = B00100000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == 'J' || inputMessage[counter] == 'j')
    {
      your_text[counter][0] = B00111000;
      your_text[counter][1] = B00010000;
      your_text[counter][2] = B00010000;
      your_text[counter][3] = B00010000;
      your_text[counter][4] = B10010000;
      your_text[counter++][5] = B01100000;
    }
    if (inputMessage[counter] == 'M' || inputMessage[counter] == 'm')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B11011000;
      your_text[counter][2] = B10101000;
      your_text[counter][3] = B10101000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'N' || inputMessage[counter] == 'n')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B11001000;
      your_text[counter][2] = B10101000;
      your_text[counter][3] = B10101000;
      your_text[counter][4] = B10011000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'L' || inputMessage[counter] == 'l')
    {
      your_text[counter][0] = B10000000;
      your_text[counter][1] = B10000000;
      your_text[counter][2] = B10000000;
      your_text[counter][3] = B10000000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == 'O' || inputMessage[counter] == 'o')
    {
      your_text[counter][0] = B01110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B10001000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B01110000;
    }
    if (inputMessage[counter] == 'P' || inputMessage[counter] == 'p')
    {
      your_text[counter][0] = B11110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B11110000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B10000000;
    }
    if (inputMessage[counter] == 'Q' || inputMessage[counter] == 'q')
    {
      your_text[counter][0] = B01110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10101000;
      your_text[counter][3] = B10011000;
      your_text[counter][4] = B01111000;
      your_text[counter++][5] = B00001000;
    }
    if (inputMessage[counter] == 'R' || inputMessage[counter] == 'r')
    {
      your_text[counter][0] = B11110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B11110000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'S' || inputMessage[counter] == 's')
    {
      your_text[counter][0] = B01110000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B01100000;
      your_text[counter][3] = B00010000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B01110000;
    }
    if (inputMessage[counter] == 'K' || inputMessage[counter] == 'k')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B10010000;
      your_text[counter][2] = B11100000;
      your_text[counter][3] = B11100000;
      your_text[counter][4] = B10010000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'T' || inputMessage[counter] == 't')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B00100000;
      your_text[counter][2] = B00100000;
      your_text[counter][3] = B00100000;
      your_text[counter][4] = B00100000;
      your_text[counter++][5] = B00100000;
    }
    if (inputMessage[counter] == 'U' || inputMessage[counter] == 'u')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B10001000;
      your_text[counter][4] = B10001000;
      your_text[counter++][5] = B01110000;
    }
    if (inputMessage[counter] == 'V' || inputMessage[counter] == 'v')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10001000;
      your_text[counter][3] = B10001000;
      your_text[counter][4] = B01010000;
      your_text[counter++][5] = B00100000;
    }
    if (inputMessage[counter] == 'W' || inputMessage[counter] == 'w')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B10001000;
      your_text[counter][2] = B10101000;
      your_text[counter][3] = B10101000;
      your_text[counter][4] = B10101000;
      your_text[counter++][5] = B01010000;
    }
    if (inputMessage[counter] == 'X' || inputMessage[counter] == 'x')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B01010000;
      your_text[counter][2] = B00100000;
      your_text[counter][3] = B00100000;
      your_text[counter][4] = B01010000;
      your_text[counter++][5] = B10001000;
    }
    if (inputMessage[counter] == 'Y' || inputMessage[counter] == 'y')
    {
      your_text[counter][0] = B10001000;
      your_text[counter][1] = B01010000;
      your_text[counter][2] = B00100000;
      your_text[counter][3] = B00100000;
      your_text[counter][4] = B00100000;
      your_text[counter++][5] = B00100000;
    }
    if (inputMessage[counter] == 'Z' || inputMessage[counter] == 'z')
    {
      your_text[counter][0] = B11111000;
      your_text[counter][1] = B00001000;
      your_text[counter][2] = B00110000;
      your_text[counter][3] = B01100000;
      your_text[counter][4] = B10000000;
      your_text[counter++][5] = B11111000;
    }
    if (inputMessage[counter] == ' ')
    {
      your_text[counter][0] = B00000000;
      your_text[counter][1] = B00000000;
      your_text[counter][2] = B00000000;
      your_text[counter][3] = B00000000;
      your_text[counter][4] = B00000000;
      your_text[counter++][5] = B00000000;
    }
  }
}
