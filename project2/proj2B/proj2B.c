#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	FILE *f_in, *f_out;
	int *buffer;

	if (argc != 3) {
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	
	buffer = malloc(sizeof(int)*100);

	int i,j;
	for(i = 0; i < 5; i++) {
		fread(buffer, sizeof(int), 5, f_in);
		for(j = 0; j < 5; j++){
			fprintf(f_out, "%d\n", buffer[j]);
		}
		fseek(f_in, 20, SEEK_CUR);

	}

//	printf("Copying %ld bytes from %s from to %s\n", sizeof(buffer), argv[1], argv[2]);

//	fwrite(buffer, sizeof(char), 25, f_out);
	
	
	fclose(f_in);
	fclose(f_out);
	free(buffer);
	return 0;



}  
