#include <stdio.h>
#include <string.h>
#include <image.h>
#include <stdlib.h>
#include <source.h>

void Image::Update() const {
	source->Update();
}

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

void Image::setSource(Source *s) {
	if (s != NULL) {
		source = s;
	}
}

int Image::getWidth() const { return this->width; };

int Image::getHeight() const { return this->height; };

void Image::setBuffer(int width, int height) { this->buffer = new Pixel[width*height]; };

Pixel* Image::getBuffer() const { return (this->buffer); };

Image::~Image() { 
	delete buffer; 
};



