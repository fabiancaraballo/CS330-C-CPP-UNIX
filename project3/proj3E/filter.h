#include <stdio.h>
#include <source.h>
#include <sink.h>


#ifndef FILTER_H
#define FILTER_H

class Filter : public Source, public Sink 
{
	public:
		virtual void Update();
};

class Shrinker : public Filter {

	public:
	       void Execute();
};

class LRCombine : public Filter {
	public:
		void Execute();
};

class TBCombine : public Filter {
	public:
		void Execute();
};

class Blender : public  Filter  {
	protected: 
		double factor;
	public:
		void SetFactor(double factor);
		void Execute();
		double getFactor();

};


#endif

