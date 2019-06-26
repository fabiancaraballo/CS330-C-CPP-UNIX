#ifndef PNMREADERCPP_H
#define PNMREADERCPP_H
#include <source.h>
#include <stdio.h>
#include <image.h>
#include <string.h>

class PNMreaderCPP : public Source {
	private:
		char* file;
		int width, height;
	public:
	       PNMreaderCPP(char *filename); 
		~PNMreaderCPP() { delete(file); }
		virtual void Execute();
};
#endif
