#include <stdlib.h>
#include <stdio.h>
#include <filter.h>
#include <image.h>
#include <source.h>
#include <sink.h>
#include <string.h>

void Filter::Update() {
	if(input1 != NULL)
		input1->Update();
	if(input2 != NULL)
		input2->Update();

	Execute();
}

void Shrinker::Execute()
{
    	int i, j;
	img.setValues(input1->getWidth() / 2, input1->getHeight() / 2);
	img.setBuffer(input1->getWidth() / 2, input1->getHeight() / 2);
        for(i = 0; i < input1->getWidth() / 2; i++) {
		for(j = 0; j < input1->getHeight() / 2; j++) {
	              img.getBuffer()[j*(input1->getWidth()/2)+i].r = input1->getBuffer()[2 * j * input1->getWidth() + 2*i].r;
		      img.getBuffer()[j*(input1->getWidth()/2)+i].g = input1->getBuffer()[2 * j * input1->getWidth() + 2*i].g;
	              img.getBuffer()[j*(input1->getWidth()/2)+i].b = input1->getBuffer()[2 * j * input1->getWidth() + 2*i].b;
		}

	}	
}

void LRCombine::Execute()
{
	 int i, j;
	 int totalWidth = input1->getWidth() + input2->getWidth();
	 int leftWidth = input1->getWidth();
	 int rightWidth = input2->getWidth();
	 int leftHeight =  input1->getHeight();
	 img.setValues(totalWidth, leftHeight);
	 img.setBuffer(totalWidth, leftHeight);
	 
	 for(i = 0; i < totalWidth; i++) {
		for(j = 0; j < leftHeight; j++) {
			if(i < leftWidth) {
				img.getBuffer()[j* totalWidth + i].r = input1->getBuffer()[j* leftWidth + i].r;
				img.getBuffer()[j* totalWidth + i].g = input1->getBuffer()[j* leftWidth + i].g;
				img.getBuffer()[j* totalWidth + i].b = input1->getBuffer()[j* leftWidth + i].b;
			}									
			else {
				 img.getBuffer()[j* totalWidth + i].r = input2->getBuffer()[j * rightWidth + (i - leftWidth)].r;
				 img.getBuffer()[j* totalWidth + i].g = input2->getBuffer()[j * rightWidth + (i - leftWidth)].g;
				 img.getBuffer()[j* totalWidth + i].b = input2->getBuffer()[j * rightWidth + (i - leftWidth)].b;
		       	}
		}
	 }
}



void TBCombine::Execute()
{
	int i;
	int topWidth = input1->getWidth();
	int totalHeight = input1->getHeight() + input2->getHeight();
	int topHeight = input1->getHeight();
	img.setValues(topWidth, totalHeight);
	img.setBuffer(topWidth, totalHeight);
	for (i = 0; i < topWidth* input1->getHeight(); i++) {
		img.getBuffer()[i].r = input1->getBuffer()[i].r;
		img.getBuffer()[i].g = input1->getBuffer()[i].g;
		img.getBuffer()[i].b = input1->getBuffer()[i].b;
	}
	for (i = 0; i < topWidth*input1->getHeight(); i++) {
		img.getBuffer()[topWidth*topHeight + i].r = input2->getBuffer()[i].r;
		img.getBuffer()[topWidth*topHeight + i].g = input2->getBuffer()[i].g;
		img.getBuffer()[topWidth*topHeight + i].b = input2->getBuffer()[i].b;
	}

} 


void Blender::SetFactor(double factor)
{
	this->factor = factor;
}

double Blender::getFactor() {
	return (this->factor);
}

void Blender::Execute()
{
	int i;
	double factor = getFactor();
	img.setValues(input1->getWidth(), input2->getHeight());
	img.setBuffer(input1->getWidth(), input2->getHeight());
	for(i = 0; i <  input2->getWidth()*input2->getHeight(); i++) {
		(img.getBuffer())[i].r = (input1->getBuffer())[i].r * factor + (input2->getBuffer())[i].r * (1.0 - factor);
		(img.getBuffer())[i].g = (input1->getBuffer())[i].g * factor + (input2->getBuffer())[i].g * (1.0 - factor);
		(img.getBuffer())[i].b = (input1->getBuffer())[i].b * factor + (input2->getBuffer())[i].b * (1.0 - factor);
	       	}		
}
