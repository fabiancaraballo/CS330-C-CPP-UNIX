#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
	char r;
	char g;
	char b;

} Pixel;


typedef struct
{	
	/*pointer to array of Pixel info*/
	Pixel *data;
	int height;
	int width;
	int maxval;
} Image;
/* info from Pixel and Image was referenced from Professor Childs youtube lecture */

Image *
ReadImage(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	Image *img;
	char magicNum[128]; 
       	
	if(f == NULL)
	{
		fprintf(stderr, "Unable to open file %s\n", filename);
		return NULL;
	}
   	
	img = (Image*)malloc(sizeof(Image));
	fscanf(f, "%s\n%d %d\n%d\n", magicNum, &img->width, &img->height, &img->maxval);

	if(strcmp(magicNum, "P6"))
	{
			fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
			free(img);
			return NULL;
	}
	
	img->data = (Pixel*)malloc(sizeof(Pixel)*img->height*img->width);
	fread(img->data, sizeof(Pixel), (img->height * img->width), f);
	fclose(f);
	return img;	

}	


void WriteImage(Image *img, const char *filename)
{
	FILE *f = fopen(filename, "wb");
	
	fprintf(f, "P6\n%d %d\n%d\n", img->width, img->height, img->maxval);
	
	fwrite(img->data, sizeof(Pixel),(img->height*img->width), f);
	
	fclose(f);

}

Image *
YellowDiagonal(Image *input)
{
	int i, j, n;
	Pixel yellow;

	Image *output;
	output = (Image*)malloc(sizeof(Image));
	
	int height = input->height;
	output->height = height;
	
	int width  = input->width;
	output->width = width;

	output->maxval = input->maxval;
	
	output->data = (Pixel*)malloc(sizeof(int) * input->height * input->width);
		
	/*RGB array for yellow(ffff00 or 255,255,0) */
	yellow.r = 0xff;
	yellow.g = 0xff;
	yellow.b = 0x00;

	/*these two for loops set the diagonal line yellow whenever i == j */
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			n = i * width + j;
			
			//color info
			Pixel color = input->data[n];
			if(i == j)
			{	
				color = yellow;
				
			}
			output->data[n] = color;
		}

	}
	return output;

}

int main(int argc, char *argv[])
{

     	/* Read an image, apply yellow diagonal to it, then write */
	const char* f_in;
	f_in = argv[1];
	
	const char* f_out;
	f_out = argv[2];
	
	Image* input;
	input = ReadImage(f_in);
	
	Image* output;
	output = YellowDiagonal(input);
	WriteImage(output, f_out);
	
	free(input->data);
	free(input); 
	free(output);
	
	return 0;

}
