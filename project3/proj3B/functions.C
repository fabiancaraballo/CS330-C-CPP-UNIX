#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>
#include <functions.h>

void ReadImage(char *filename, Image &output) {
	
	//used from 3A
	FILE *f = fopen(filename, "rb");
	char magicNum[128];
	int width;
	int height;
	int maxval;


	if(strcmp(magicNum, "P6")) {
		fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
	}
	
	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
	
	 if(f == NULL) {
		fprintf(stderr, "Unable to open file %s\n", filename);
	}
								    
	output.width = width;
	output.height = height;
	output.buffer = (Pixel *) malloc(height * width * sizeof(Pixel));
	fread(output.buffer, sizeof(Pixel), width*height, f);
	fclose(f);	
}

void WriteImage(char *filename, Image &img){
	
	FILE *f = fopen(filename, "wb");
	fprintf(f, "P6\n%d %d\n255\n", img.width, img.height);
	fwrite(img.buffer, sizeof(Pixel), img.height*img.width, f);
	fclose(f);
}

void HalfSize(Image &input, Image &output) {
	
	int i, j;
	//only allocate for only half of the memory of the input image
	output.width = (int)(input.width) / 2;
	output.height = (int)(input.height) / 2;
	output.buffer = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));

	//this for loop will add half of the input buffer into the output buffer
	for(i = 0; i < output.width; i++) {
		for(j = 0; j < output.height; j++) {
			output.buffer[j*output.width+i].r = input.buffer[4 * j * output.width + 2*i].r;
			output.buffer[j*output.width+i].g = input.buffer[4 * j * output.width + 2*i].g;
			output.buffer[j*output.width+i].b = input.buffer[4 * j * output.width + 2*i].b;
		}
	}
}

void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output) {
	
	int i, j;
	//since we are combine the left and right images, the output width becomes the larger.
	//the width of the left image plus the width of the right image 
	output.width = leftInput.width + rightinput.width;
	//in this case, the height does not matter since we are just putting two images together side by side
	//we assume both images are the same height so we can take either the height of the left or right img
	//in this case I just took the left height and made that the height of the output
	output.height = leftInput.height;
	output.buffer = (Pixel *)malloc(output.width * output.height * sizeof(Pixel));
	//this for loop adds all the pixels from the left buffer into the output buffer, then once that is done
	//it moves on to add all of the right pixels into the output buffer which will
	//ensure that the left and right images are basically linked together
	for(i = 0; i < output.width; i++) {
		for(j = 0; j < output.height; j++) {
				
			if(i < leftInput.width) {
				output.buffer[j*output.width+i].r = leftInput.buffer[j* leftInput.width + i].r;
				output.buffer[j*output.width+i].g = leftInput.buffer[j* leftInput.width + i].g;
				output.buffer[j*output.width+i].b = leftInput.buffer[j* leftInput.width + i].b;
			}
			else {
				output.buffer[j*output.width+i].r = rightinput.buffer[j * rightinput.width + (i - leftInput.width)].r;
				output.buffer[j*output.width+i].g = rightinput.buffer[j * rightinput.width + (i - leftInput.width)].g;
				output.buffer[j*output.width+i].b = rightinput.buffer[j * rightinput.width + (i - leftInput.width)].b;
			}
		}
	}
}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output) {

	
	int i;
	//sort of similar to LeftRightCombine but in this case we are changing the height instead of the 
	//width, so we can set the output height to either the top or bottom input images
	//in this case I just chose the top image
	output.width = topInput.width;
	//the height is different because we are going to combine the topInput image with the bottom left
	//input image so we basically link both images together
	//which means the output height is going to be the topheight plus the bottomheight
	output.height = topInput.height + bottomInput.height;
	output.buffer = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));
	
	//these two for loops one by one add the topInput image pixels into the output buffer so we can ensure the topInput is place in the buffer first
	//once the top image is fully in the output, the second for loops ensures that
	//the bottom input image will be placed in the output buffer
	//which will then ensure both images are linked together
	for (i = 0; i < topInput.height * topInput.width; i++) {
		output.buffer[i].r = topInput.buffer[i].r; 
		output.buffer[i].g = topInput.buffer[i].g; 
		output.buffer[i].b = topInput.buffer[i].b; 
	}

	for (i = 0; i < topInput.width*topInput.height; i++) {
		 output.buffer[topInput.width * topInput.height + i].r = bottomInput.buffer[i].r;
		 output.buffer[topInput.width * topInput.height + i].g = bottomInput.buffer[i].g;
		 output.buffer[topInput.width * topInput.height + i].b = bottomInput.buffer[i].b;
	}



}

void Blend(Image &input1, Image &input2, double factor, Image &output) {
		
		int i;
		//the width and height of this output image is going to be the size of the first image, input1
		//because what this function does is basically replace a percentage(factor) of image1 with image2.
		//so the height and width are going to be determine by input1
		output.width = input1.width;	
		output.height = input1.height;
		output.buffer = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));	
		// this for loops takes the percentage(factor) of image1's pixels, and fills the remaining(1-factor) with image2's pixels
		// which will ensure that both images get blended together
		for(i = 0; i <  output.width*output.height; i++) {
			(output.buffer)[i].r = (input1.buffer)[i].r * factor + (input2.buffer)[i].r * (1.0 - factor);	
			(output.buffer)[i].g = (input1.buffer)[i].g * factor + (input2.buffer)[i].g * (1.0 - factor);	
			(output.buffer)[i].b = (input1.buffer)[i].b * factor + (input2.buffer)[i].b * (1.0 - factor);	
		}
}

