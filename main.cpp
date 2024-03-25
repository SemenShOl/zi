#include <iostream>
#include <fstream>
#include <bitset>

#define ORIGINALFILENAME "./original.bmp"
#define COPYFILENAME "./original copy.bmp"

using namespace std;

int main() {
  ifstream Fin1(ORIGINALFILENAME, ios::binary);
  ifstream Fin2(COPYFILENAME, ios::binary);

  Fin1.seekg(54);
  Fin2.seekg(54);

  streampos Fin1Pos = Fin1.tellg();
  streampos Fin2Pos = Fin2.tellg();

  cout << "Fin1 position: " << Fin1Pos << endl;
  cout << "Fin2 position: " << Fin2Pos << endl;

  for(int i = 0; i < 10; i++) {
    char byte1;
    char byte2;

    Fin1.read(&byte1, 1);
    Fin2.read(&byte2, 1);

    cout << "Byte 1: " << bitset<8>(byte1) << " " << "Byte 2: " << bitset<8>(byte2) << endl;
  }

  Fin1.close();
  Fin2.close();

  return 0;
}
