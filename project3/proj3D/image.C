#include <stdio.h>
#include <image.h>
#include <stdlib.h>

Image::Image(void) {
	this->width = 0;
	this->height = 0;
	this->buffer = NULL;
}

Image::Image(int w, int h) {
	this->width = w;
	this->height = h;
	Pixel *buffer = new Pixel[width*height];
};

Image::Image(Image &img) {
	width = img.width;
	height = img.height;
	Pixel *buffer = new Pixel[width*height];
	int i;
	for(i = 0; i < img.width * img.height; i++) {
		buffer[i] = img.buffer[i];
	}
};

void Image::setValues(int w, int h) {
	        this->width = w;
		this->height = h;
};

void Image::ResetValues(int w, int h) {
	this->width = w;
	this->height = h;
};

int Image::getWidth() { return this->width; };

int Image::getHeight() { return this->height; };

void Image::setBuffer(int width, int height) { this->buffer = new Pixel[width*height]; };

Pixel* Image::getBuffer() { return (this->buffer); };

Image::~Image() { 
	delete buffer; 
};



