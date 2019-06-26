#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <image.h>

class Source {
	protected:
		Image img;
	 
	public:
		Image *GetOutput();
		virtual void Execute() = 0;

};

#endif


