#include <iostream>
#include <cstdint>
#include <fstream>
#include "./bmp/bmp.h"
#include <bitset>

#define FILEPATH "./6.bmp"

using namespace std;
uint8_t get_byte_from_pixel(RGBQUAD *pixel)
{
  uint8_t byte = 0b00000000;

  byte |= pixel->rgbReserved & 0b00000011;
  byte |= (pixel->rgbRed & 0b00000011) << 2;
  byte |= (pixel->rgbGreen & 0b00000011) << 4;
  byte |= (pixel->rgbBlue & 0b00000011) << 6;

  return byte;
}

void hide_byte_into_pixel(RGBQUAD *pixel, uint8_t hide_byte)
{
  pixel->rgbBlue &= (0xFC);
  pixel->rgbBlue |= (hide_byte >> 6) & 0x3;
  pixel->rgbGreen &= (0xFC);
  pixel->rgbGreen |= (hide_byte >> 4) & 0x3;
  pixel->rgbRed &= (0xFC);
  pixel->rgbRed |= (hide_byte >> 2) & 0x3;
  pixel->rgbReserved &= (0xFC);
  pixel->rgbReserved |= (hide_byte) & 0x3;
}

int main()
{
  ifstream picture(FILEPATH, ios::binary);

  BITMAPFILEHEADER file_header;
  BITMAPINFOHEADER BITMAP_header;

  picture.read(reinterpret_cast<char *>(&file_header), sizeof(BITMAPFILEHEADER));
  picture.read(reinterpret_cast<char *>(&BITMAP_header), sizeof(BITMAPINFOHEADER));

  for (int i = 0; i < BITMAP_header.biWidth; i++)
  {
    for (int j = 0; j < BITMAP_header.biHeight; j++)
    {
      RGBQUAD pixel;
      picture.read(reinterpret_cast<char *>(&pixel.rgbBlue), sizeof(uint8_t));
      picture.read(reinterpret_cast<char *>(&pixel.rgbGreen), sizeof(uint8_t));
      picture.read(reinterpret_cast<char *>(&pixel.rgbRed), sizeof(uint8_t));
      picture.read(reinterpret_cast<char *>(&pixel.rgbReserved), sizeof(uint8_t));

      uint8_t received_byte = get_byte_from_pixel(&pixel);
      cout << static_cast<char>(received_byte);
      if (received_byte == 0xFF)
      {
        return 0;
      }
    }
  }

  picture.close();

  return 0;
}
