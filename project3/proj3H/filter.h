#include <stdio.h>
#include "source.h"
#include "sink.h"


#ifndef FILTER_H
#define FILTER_H

class Filter : public Source, public Sink 
{
	public:
		virtual void Update();
		virtual const char *FilterName() = 0;
		virtual const char *SourceName();
		virtual const char *SinkName();
		
};

class CheckSum : public Sink {
	public:
		void OutputCheckSum(const char *filename);
		const char *SinkName() { return "CheckSum"; }
};

class Rotate : public Filter {
	public:
		virtual void Execute();
		virtual const char *FilterName() { return "Rotate"; }

};

class Grayscale : public Filter {
	public:
	virtual void Execute();
	virtual const char *FilterName() { return "Grayscale"; }
};

class Blur : public Filter { 
	public:
		virtual void Execute();
		virtual const char *FilterName() { return "Blur"; }
};

class Mirror : public Filter {
	public:
	virtual void Execute();
	virtual const char *FilterName() { return "Mirror"; }

};

class Color : public Source {
	protected:
		int width, height;
		unsigned char red;
		unsigned char blue;
		unsigned char green;

	public:
	       Color(int w, int h, unsigned char r, unsigned char g, unsigned char b) {
		       width = w;
		       height = h;
		       red = r;
		       green = g;
		       blue = b;
		}
       	       //~Color();
	       virtual void Update();
	       void Execute();
	       virtual const char *SourceName() {return "Color"; }		
};

class Subtract : public Filter {
	public:
		void Execute();
		virtual const char *FilterName();

};


class Shrinker : public Filter {

	public:
	       void Execute();
	       virtual const char *FilterName();
};

class LRCombine : public Filter {
	public:
		void Execute();
		virtual const char *FilterName();
};

class TBCombine : public Filter {
	public:
		void Execute();
		virtual const char *FilterName();
};

class Blender : public  Filter  {
	protected: 
		double factor;
	public:
		void SetFactor(double factor);
		void Execute();
		double getFactor();
		 virtual const char *FilterName();

};


#endif

