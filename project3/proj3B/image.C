#include <stdio.h>
#include <image.h>
#include <stdlib.h>


Image::Image(void) {

	
	width = 0;
	height = 0;
	buffer = NULL;
}

Image::Image(int w, int h) {
	
	width = w;
	height = h;
	Pixel *buffer = (Pixel *)malloc(sizeof(Pixel)  * height * width);
}

Image::Image(Image &img) {
	
	width = img.width;
	height = img.height;
	Pixel *buffer = (Pixel*)malloc(sizeof(Pixel)  * height * width);
	int i;
	for(i = 0; i < img.width * img.height; i++) {
		buffer[i] = img.buffer[i];
	}
}

void Image::ResetSize(int w, int h) {
	
	width = w;
	height = h;

}
Pixel* Image::getBuffer() {
	return buffer;
}


	

