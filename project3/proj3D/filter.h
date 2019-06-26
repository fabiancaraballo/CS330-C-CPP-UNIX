#include <stdio.h>
#include <source.h>
#include <sink.h>


#ifndef FILTER_H
#define FILTER_H

class filter : public Source, public Sink 
{
};

class Shrinker : public filter {

	public:
	       void Execute();
};

class LRCombine : public filter {
	public:
		void Execute();
};

class TBCombine : public filter {
	public:
		void Execute();
};

class Blender : public  filter  {
	protected: 
		double factor;
	public:
		void SetFactor(double factor);
		void Execute();
		double getFactor();

};


#endif

