#include <iostream>
#include <cstdint>
#include <fstream>
#include "./bmp/bmp.h"

#define FILEPATH "./original.bmp"

using namespace std;

int main() {
  ifstream Fin(FILEPATH, ios::binary);

  BITMAPFILEHEADER bmpFileHeader;
  BITMAPINFOHEADER bmpInfoHeader;

  Fin.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));
  Fin.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BITMAPINFOHEADER));

  for(int i = 0; i < bmpInfoHeader.biWidth; i++) {
    for(int j = 0; j < bmpInfoHeader.biHeight; j++) {
      RGBQUAD pixel;

      Fin.read(reinterpret_cast<char*>(&pixel.blue), sizeof(uint8_t));
      Fin.read(reinterpret_cast<char*>(&pixel.green), sizeof(uint8_t));
      Fin.read(reinterpret_cast<char*>(&pixel.red), sizeof(uint8_t));
      Fin.read(reinterpret_cast<char*>(&pixel.reserved), sizeof(uint8_t));

      uint8_t extractedByte = extractByte(&pixel);
      cout << static_cast<char>(extractedByte);
    }
  }

  Fin.close();

  return 0;
}
