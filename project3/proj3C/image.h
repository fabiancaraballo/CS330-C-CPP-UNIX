#include <stdio.h>
#ifndef IMAGE_H
#define IMAGE_H

struct Pixel { 
	unsigned char r,g,b;
};

class Image {
	private:
		Pixel *buffer;
		int width, height, maxval;
	public:
		Image(void);
		void setValues(int w, int h);
		Image(int w, int h);
		Image(Image &);	
		void ResetValues(int w, int h);	
		int getWidth();
		int getHeight();
		int getMaxval(); 
		Pixel* getBuffer();
		void setBuffer(int, int);
		~Image();

};

#endif


