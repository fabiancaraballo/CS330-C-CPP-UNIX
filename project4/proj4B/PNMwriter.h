#ifndef PNMWRITER_H
#define PNMWRITER_H
#include <stdio.h>
#include "sink.h"

class PNMwriter: public Sink {
	public:
		void Write(char *file);
};

#endif
