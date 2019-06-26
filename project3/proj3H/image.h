#include <stdio.h>
#ifndef IMAGE_H
#define IMAGE_H
class Source; 

struct Pixel { 
	unsigned char r,g,b;
};

class Image {
	private:
		Pixel *buffer;
		int width, height, maxval;
		Source *source;
	public:
		Image(void);
		void setValues(int w, int h);
		void setSource(Source *s);
		Image(int w, int h);
		Image(Image &);	
		void ResetValues(int w, int h);	
		int getWidth() const;
		int getHeight() const;
		int getMaxval(); 
		Pixel* getBuffer() const;
		void Update() const;
		void setBuffer(int, int);
		~Image();

};

#endif


