#include <iostream>
#include <cstdint>
#include <bitset>
#include "./bmp.h"

using namespace std;

void printPixel(RGBQUAD* pixel) {
  cout << "Blue: " << bitset<8>(pixel->blue) << endl;
  cout << "Green: " << bitset<8>(pixel->green) << endl;
  cout << "Red: " << bitset<8>(pixel->red) << endl;
  cout << "Reserved: " << bitset<8>(pixel->reserved) << endl;
}

void hideByte(RGBQUAD* pixel, uint8_t byte) {
  pixel->blue &= (0b11111100);
  pixel->blue |= (byte >> 6) & 0b00000011;

  pixel->green &= (0b11111100);
  pixel->green |= (byte >> 4) & 0b00000011;

  pixel->red &= (0b11111100);
  pixel->red |= (byte >> 2) & 0b00000011;

  pixel->reserved &= (0b11111100);
  pixel->reserved |= (byte) & 0b00000011;
}

uint8_t extractByte(RGBQUAD* pixel) {
  uint8_t byte = 0b00000000;

  byte |= pixel->reserved & 0b00000011;
  byte |= (pixel->red & 0b00000011) << 2;
  byte |= (pixel->green & 0b00000011) << 4;
  byte |= (pixel->blue & 0b00000011) << 6;

  return byte;
}