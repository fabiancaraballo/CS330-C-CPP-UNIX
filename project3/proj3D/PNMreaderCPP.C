#include <PNMreaderCPP.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>
#include <source.h>

#include <iostream>
#include <fstream>


using namespace std;

PNMreaderCPP::PNMreaderCPP(char *filename) {
	file = new char[strlen(filename) +1];
	int i;
	for(i = 0;i < strlen(filename); i++) {
		file[i] = filename[i];
	}
};


void PNMreaderCPP::Execute() {
	
	ifstream ifs;
	ifs.open(file, ios::binary);
	
	char magicNum[128];
	int width, height, maxval;


	ifs >> magicNum >> width >> height >> maxval;
	ifs.ignore(256, '\n');


	img.setValues(width, height);
	img.setBuffer(width, height);

	cout << magicNum << " " << width << " " << height << " " << maxval << endl;

	ifs.read((char *) img.getBuffer(),3 * width * height);

	ifs.close();

}

