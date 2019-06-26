#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <image.h>
#include <stdlib.h>

class Source {
	protected:
		Image img;
		virtual void Execute() = 0;	 
	public:
		Source() {
			img.setSource(this);
		}
		Image *GetOutput(void);
		virtual void Update();

};

#endif


