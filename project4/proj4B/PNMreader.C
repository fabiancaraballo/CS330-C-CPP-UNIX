#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <PNMreader.h>
#include <image.h>
#include "source.h"

PNMreader::PNMreader(char *filename) {

	f = new char[strlen(filename)+1];
	int i;
	for(i = 0; i < strlen(filename)+1; i++) {
		f[i] = filename[i];
	}
}

void PNMreader::Execute() {

	FILE *f_in = fopen(f, "rb"); //try fixing here;
	char magicNum[128];
	int width;
	int height;
	int maxval;
	Image* newImg = GetOutput();
	
	fscanf(f_in, "P6\n%d %d\n255\n", &width, &height);

	newImg->setValues(width, height);
	newImg->setBuffer(width, height);
	
	
	
	fread(newImg->getBuffer(), sizeof(Pixel), newImg->getHeight() * newImg->getWidth(), f_in);
	fclose(f_in);
}

PNMreader::~PNMreader() { 
	delete[] f; 
};





