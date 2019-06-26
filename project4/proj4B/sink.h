#include "image.h"

#ifndef SINK_H
#define SINK_H

class Sink {
	protected: 
		const Image *input1;
		const Image *input2;
	public:
		Sink() {
			input1 = NULL;
			input2 = NULL;
		}
		void SetInput(Image *input1);
		void SetInput2(Image *input2);

};

#endif



