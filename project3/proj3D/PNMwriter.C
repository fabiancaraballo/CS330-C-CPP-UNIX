#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <PNMwriter.h>
#include <image.h>
#include <sink.h>

void PNMwriter::Write(char *file) {

	FILE *f_out = fopen(file, "w");
	fprintf(f_out, "P6\n%d %d\n255\n", input1->getWidth(), input1->getHeight());
	fwrite(input1->getBuffer(), sizeof(Pixel), input1->getWidth()*input1->getHeight(), f_out);
	fclose(f_out);

}
