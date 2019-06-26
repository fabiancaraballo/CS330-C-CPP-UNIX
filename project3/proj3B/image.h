#ifndef IMAGE_H
#define IMAGE_H

struct Pixel {
	unsigned char r,g,b;
};

struct Image {
	int width, height, maxval;
	Pixel *buffer;
	Image(void);
	Image(int w, int h);
	void ResetSize(int width, int height);
	Pixel* getBuffer();
	Image(Image &);
};
#endif
