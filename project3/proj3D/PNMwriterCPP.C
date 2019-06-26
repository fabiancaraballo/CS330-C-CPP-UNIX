#include <PNMwriterCPP.h>
#include <iostream>
#include <fstream>

using namespace std;

void PNMwriterCPP::Write(char *filename) {

		int width = input1->getWidth();
		int height = input1->getHeight();
		
		ofstream ofs;

		ofs.open(filename, ios::binary);

		ofs << "P6" << endl;
		ofs << width << " " << height <<  endl;
		ofs << 255 << endl;

		ofs.write((char *) input1->getBuffer(), 3 *  width * height);

		ofs.close();

}
