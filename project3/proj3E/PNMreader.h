#include <stdio.h>
#include <source.h>

#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader : public Source {
	protected: 
		char *file;
		char *f;
	public:
		virtual void Execute();
		PNMreader(char *file);
		~PNMreader();
};



#endif
