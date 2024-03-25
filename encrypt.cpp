#include <iostream>
#include <cstdint>
#include <fstream>
#include "./bmp/bmp.h"

#define FILEPATH "original.bmp"

using namespace std;

int main() {
  string message;
  cin >> message;
  cout << message << endl;

  uint8_t* messageByteSet = new uint8_t[message.length() + 1];

  for(int i = 0; i < message.length(); i++) {
    messageByteSet[i] = static_cast<uint8_t>(message[i]);
  }

  messageByteSet[message.length()] = 0xFF;

  for(int i = 0; i < message.length() + 1; i++) {
    std::cout << messageByteSet[i] << std::endl;
  }

  ifstream Fin(FILEPATH, ios::binary);

  BITMAPFILEHEADER bmpFileHeader;
  BITMAPINFOHEADER bmpInfoHeader;

  Fin.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));
  Fin.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BITMAPINFOHEADER));

  RGBQUAD* pixels = new RGBQUAD[message.length()];

  streampos finPosition = Fin.tellg();

  for(int i = 0; i < message.length(); i++) {
    RGBQUAD pixel;

    Fin.read(reinterpret_cast<char*>(&pixel.blue), sizeof(uint8_t));
    Fin.read(reinterpret_cast<char*>(&pixel.green), sizeof(uint8_t));
    Fin.read(reinterpret_cast<char*>(&pixel.red), sizeof(uint8_t));
    Fin.read(reinterpret_cast<char*>(&pixel.reserved), sizeof(uint8_t));

    pixels[i] = pixel;
  }

  Fin.close();

  ofstream Fout(FILEPATH, ios::binary | ios::in | ios::ate);
  Fout.seekp(finPosition);

  streampos foutPosition = Fout.tellp();
  cout << "Fin position: " << finPosition << endl;
  cout << "Fout position: " << foutPosition << endl;

  cout << "message len: " <<  message.length() << endl;

  for(int i = 0; i < message.length(); i++) {
    RGBQUAD newPixel = pixels[i];

    cout << "Old pixel: " << endl;
    printPixel(&newPixel);

    hideByte(&newPixel, messageByteSet[i]);

    cout << "New pixel" << endl;
    printPixel(&newPixel);
    cout << endl;

    Fout.put(newPixel.blue);
    Fout.put(newPixel.green);
    Fout.put(newPixel.red);
    Fout.put(newPixel.reserved);
  }

  streampos foutPosition2 = Fout.tellp();
  cout << "Fout position: " << foutPosition2<< endl;
  
  Fout.close();

  return 0;
}
