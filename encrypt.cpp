#include <iostream>
#include <cstdint>
#include <fstream>
#include "./bmp/bmp.h"
#include <bitset>

#define FILEPATH "6.bmp"

using namespace std;

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
uint8_t get_byte_from_pixel(RGBQUAD *pixel)
{
  uint8_t byte = 0b00000000;

  byte |= pixel->rgbReserved & 0b00000011;
  byte |= (pixel->rgbRed & 0b00000011) << 2;
  byte |= (pixel->rgbGreen & 0b00000011) << 4;
  byte |= (pixel->rgbBlue & 0b00000011) << 6;

  return byte;
}

void fill_binary_message(uint8_t *binary_message, string message)
{
  for (int i = 0; i < message.length(); i++)
  {
    binary_message[i] = static_cast<uint8_t>(message[i]);
  }

  binary_message[message.length()] = 0xFF;
}

int main()
{
  string message;
  cin >> message;
  // cout << message << endl;

  uint8_t *binary_message = new uint8_t[message.length() + 1];

  // for (int i = 0; i < message.length(); i++)
  // {
  //   binary_message[i] = static_cast<uint8_t>(message[i]);
  // }

  // binary_message[message.length()] = 0xFF;

  fill_binary_message(binary_message, message);

  RGBQUAD *pixels = new RGBQUAD[message.length()];
  ifstream pictureIN(FILEPATH, ios::binary);
  BITMAPFILEHEADER file_header;
  BITMAPINFOHEADER BITMAP_header;

  pictureIN.read(reinterpret_cast<char *>(&file_header), sizeof(BITMAPFILEHEADER));
  pictureIN.read(reinterpret_cast<char *>(&BITMAP_header), sizeof(BITMAPINFOHEADER));

  streampos picture_starts = pictureIN.tellg();

  for (int i = 0; i < message.length(); i++)
  {
    RGBQUAD pixel;

    pictureIN.read(reinterpret_cast<char *>(&pixel.rgbBlue), sizeof(uint8_t));
    pictureIN.read(reinterpret_cast<char *>(&pixel.rgbGreen), sizeof(uint8_t));
    pictureIN.read(reinterpret_cast<char *>(&pixel.rgbRed), sizeof(uint8_t));
    pictureIN.read(reinterpret_cast<char *>(&pixel.rgbReserved), sizeof(uint8_t));

    pixels[i] = pixel;
  }

  pictureIN.close();

  ofstream pictureOUT(FILEPATH, ios::binary | ios::in | ios::ate);
  pictureOUT.seekp(picture_starts);

  streampos foutPosition = pictureOUT.tellp();
  // cout << "Fin position: " << picture_starts << endl;
  // cout << "Fout position: " << foutPosition << endl;

  // cout << "message len: " << message.length() << endl;

  for (int i = 0; i < message.length(); i++)
  {
    RGBQUAD newPixel = pixels[i];

    // cout << "Old pixel: " << endl;s
    // printPixel(&newPixel);

    hide_byte_into_pixel(&newPixel, binary_message[i]);

    // cout << "New pixel" << endl;
    // printPixel(&newPixel);
    cout << endl;

    pictureOUT.put(newPixel.rgbBlue);
    pictureOUT.put(newPixel.rgbGreen);
    pictureOUT.put(newPixel.rgbRed);
    pictureOUT.put(newPixel.rgbReserved);
  }

  // streampos foutPosition2 = pictureOUT.tellp();
  // cout << "Fout position: " << foutPosition2 << endl;

  pictureOUT.close();

  return 0;
}
