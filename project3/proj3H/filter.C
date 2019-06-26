#include <stdlib.h>
#include <stdio.h>
#include <filter.h>
#include <image.h>
#include <source.h>
#include <sink.h>
#include <string.h>
#include <logging.h>

void Filter::Update() {
	char msg[128];

	if (input1 == &this->img || input2 == &this->img)
	{
		char msg[1024];
		sprintf(msg, "%s: circular dependency!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(input1 != NULL) {
		sprintf(msg, "%s: about to update input1\n", FilterName());
		Logger::LogEvent(msg);
		input1->Update();
		sprintf(msg, "%s: done updating input1\n", FilterName());
		Logger::LogEvent(msg);
	}

	if(input2 != NULL) {
		sprintf(msg, "%s: about to update input2\n", FilterName());
		Logger::LogEvent(msg);
		input2->Update();
		sprintf(msg, "%s: done updating input1\n", FilterName());
		Logger::LogEvent(msg);
	}

	sprintf(msg, "%s: about to execute\n", FilterName());
	Logger::LogEvent(msg);
	Execute();
	sprintf(msg, "%s: done executing\n", FilterName());
	Logger::LogEvent(msg);

}

const char *Filter::SourceName() {
	        return FilterName();
}

const char *Filter::SinkName() {
	        return FilterName();
}

const char *Shrinker:: FilterName() {
	return "Shrinker";
}

const char *LRCombine:: FilterName() {
	return "LRConcat";
}

const char *TBCombine:: FilterName() {
	return "TBConcat";
}

const char *Blender:: FilterName() {
	return "Blender";
}

const char *Subtract:: FilterName() {
	        return "Subtract";
}



void Shrinker::Execute()
{
	if(input1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

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

	 if(input1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		 throw e;
	 }
	 if(input2 == NULL) {
	 	char msg[1024];
       		sprintf(msg, "%s: no input2!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	 int i, j;
	 int totalWidth = input1->getWidth() + input2->getWidth();
	 int leftWidth = input1->getWidth();
	 int rightWidth = input2->getWidth();
	 int leftHeight =  input1->getHeight();
	 img.setValues(totalWidth, leftHeight);
	 img.setBuffer(totalWidth, leftHeight);
	
	 if(input1->getHeight() != input2->getHeight()) {
		 char msg[1024];
		 //continue here
		 sprintf(msg,"%s: heights must match %d %d\n", SinkName(), input1->getHeight(), input2->getHeight());
		 DataFlowException e(SinkName(), msg);
		 throw e; 
	}

		 
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

	if(input1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(input2 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input2!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int i;
	int topWidth = input1->getWidth();
	int totalHeight = input1->getHeight() + input2->getHeight();
	int topHeight = input1->getHeight();
	img.setValues(topWidth, totalHeight);
	img.setBuffer(topWidth, totalHeight);

	if(input1->getWidth() != input2->getWidth()) {
		char msg[1024];
		sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(),input1->getWidth(),input2->getWidth());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	
	for (i = 0; i < topWidth*input1->getHeight(); i++) {
		img.getBuffer()[i].r = input1->getBuffer()[i].r;
		img.getBuffer()[i].g = input1->getBuffer()[i].g;
		img.getBuffer()[i].b = input1->getBuffer()[i].b;
	}
	for (i = 0; i < topWidth*input2->getHeight(); i++) {
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
	if(input1 == NULL) {
		char msg[1024];
		 sprintf(msg, "%s: no input1!\n", SinkName());
		 DataFlowException e(SinkName(), msg);
		 throw e;
	}
	if(input2 == NULL) { 
		char msg[1024];
		sprintf(msg, "%s: no input2!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}



	int i;
	double factor = getFactor();
	img.setValues(input1->getWidth(), input2->getHeight());
	img.setBuffer(input1->getWidth(), input2->getHeight());

	if(input1->getWidth() != input2->getWidth() || input1->getHeight() != input2->getHeight()){
		char msg[1024];
		sprintf(msg, "%s: image size must match: %d x %d, %d x %d\n", SinkName(), input1->getWidth(), input2->getWidth(), input1->getHeight(), input2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(factor > 1.0) {
		char msg[1024];
		sprintf(msg, "%s: Invalid factor for Blender: %f\n", SinkName(), factor);
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	for(i = 0; i <  input2->getWidth()*input2->getHeight(); i++) {
		(img.getBuffer())[i].r = (input1->getBuffer())[i].r * factor + (input2->getBuffer())[i].r * (1.0 - factor);
		(img.getBuffer())[i].g = (input1->getBuffer())[i].g * factor + (input2->getBuffer())[i].g * (1.0 - factor);
		(img.getBuffer())[i].b = (input1->getBuffer())[i].b * factor + (input2->getBuffer())[i].b * (1.0 - factor);
	       	}		
}


void Mirror::Execute() {
	
	if(input1 == NULL) {
		char msg[1024];
		sprintf(msg," %s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	int i, j;
	int width = input1->getWidth();
	int height = input1->getHeight();

	img.setValues(width, height);
	img.setBuffer(width, height);

	for(i = 0; i < width; i++) {
		for(j = 0; j < height; j++) {
			img.getBuffer()[j*width+i].r = input1->getBuffer()[j*width + (width-i-1)].r;
			img.getBuffer()[j*width+i].g = input1->getBuffer()[j* width + (width-i-1)].g;
			img.getBuffer()[j*width+i].b = input1->getBuffer()[j* width + (width-i-1)].b;
		}
	}	
}

void Rotate::Execute() {

	if(input1 == NULL) {
		char msg[1024];
		sprintf(msg,"%s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int i, j, newHeight;
	int width = input1->getWidth();
	int height = input1->getHeight();
	img.setValues(height, width);
	img.setBuffer(height, width);
	for(i = 0, newHeight = height - 1; i < height; ++i, --newHeight) {
		int offSet = i * width;
		for(j = 0; j < width; j++) {
			img.getBuffer()[(j*height) + newHeight].r = input1->getBuffer()[offSet + j].r;
			img.getBuffer()[(j*height) + newHeight].g = input1->getBuffer()[offSet + j].g;
			img.getBuffer()[(j*height) + newHeight].b = input1->getBuffer()[offSet + j].b;
		}
	}
}

void Subtract::Execute() {
	        
		if(input1 == NULL) {
			char msg[1024];
			sprintf(msg,"%s: no input1!\n", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
		}
		

		if(input2 == NULL) {
			char msg[1024];
			sprintf(msg,"%s: no input2!\n", SinkName());
			DataFlowException e(SinkName(), msg);
			throw e;
		}

		if(input1->getWidth() != input2->getWidth() || input1->getHeight() != input2->getHeight()){
			char msg[1024];
			sprintf(msg, "%s: image size must match: %d x %d, %d x %d\n", SinkName(), input1->getWidth(), input2->getWidth(), input1->getHeight(), input2->getHeight());
			DataFlowException e(SinkName(), msg);
			throw e;
		}

		
		int i, j, newR, newG, newB;
		int width = input1->getWidth();
		int height = input1->getHeight();
		img.ResetValues(width, height);
		img.setBuffer(width, height);
		for(i = 0; i < width; i++) {
			for(j = 0; j < height; j++) {
				int newR = (input1->getBuffer()[j*width+i].r) - (input2->getBuffer()[j*width+i].r);
				int newG = (input1->getBuffer()[j*width+i].g) - (input2->getBuffer()[j*width+i].g);
				int newB = (input1->getBuffer()[j*width+i].b) - (input2->getBuffer()[j*width+i].b);
				
				if(newR >= 0) {
					img.getBuffer()[j*width+i].r = newR;
				}
				else {
					img.getBuffer()[j*width+i].r = 0;
				}
				
				if(newG >= 0) {
					img.getBuffer()[j*width+i].g = newG;
				}
				else {					                     
					img.getBuffer()[j*width+i].g = 0;
				}
				
				if(newB >= 0) {
					img.getBuffer()[j*width+i].b = newB;
				}
				else {
					img.getBuffer()[j*width+i].b = 0;
				}
	

		}
	}

}

void Grayscale::Execute() {
	
	 if(input1 == NULL) {
		 char msg[1024];
		 sprintf(msg,"%s: no input1!\n", SinkName());
		 DataFlowException e(SinkName(), msg);
		 throw e;
	}

	int i, j;
	int width = input1->getWidth();
	int height = input1->getHeight();
	img.setValues(width, height);
	img.setBuffer(width, height);
	for(i = 0; i < width; i++) {
		for(j = 0; j < height; j++) {
			img.getBuffer()[j* width + i].r = input1->getBuffer()[j* width + i].r/5 + input1->getBuffer()[j* width + i].g/2 + input1->getBuffer()[j* width + i].b/4;
			img.getBuffer()[j* width + i].g = input1->getBuffer()[j* width + i].r/5 + input1->getBuffer()[j* width + i].g/2 + input1->getBuffer()[j* width + i].b/4;
			img.getBuffer()[j* width + i].b = input1->getBuffer()[j* width + i].r/5 + input1->getBuffer()[j* width + i].g/2 + input1->getBuffer()[j* width + i].b/4;
		}
	}

} 

void Blur::Execute() {

	if(input1 == NULL) {
		char msg[1024];
		sprintf(msg,"%s: no input1!\n", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int i, j;
	int width = input1->getWidth();
	int height = input1->getHeight();
	img.ResetValues(width, height);
	img.setBuffer(width, height);
	for(i = 0; i < width; i++) {
		for(j = 0; j < height; j++) {
			if(i == 0 || j == 0 || i == (width-1) || j == (height-1)) {

				img.getBuffer()[j* width + i].r = input1->getBuffer()[j* width + i].r;
				img.getBuffer()[j* width + i].g = input1->getBuffer()[j* width + i].g;
				img.getBuffer()[j* width + i].b = input1->getBuffer()[j* width + i].b;
			}
			else {
				img.getBuffer()[j* width + i].r = input1->getBuffer()[(j-1)* width +(i-1)].r/8 + input1->getBuffer()[j* width +(i-1)].r/8 + input1->getBuffer()[(j+1) * width + (i-1)].r/8 + input1->getBuffer()[(j-1) * width + i].r/8 + input1->getBuffer()[(j+1) * width + i].r/8 +input1->getBuffer()[(j-1) * width + (i+1)].r/8 + input1->getBuffer()[j* width +(i+1)].r/8 + input1->getBuffer()[(j+1)* width + (i+1)].r/8;
				
				img.getBuffer()[j* width + i].g = input1->getBuffer()[(j-1)* width +(i-1)].g/8 + input1->getBuffer()[j* width +(i-1)].g/8 + input1->getBuffer()[(j+1) * width + (i-1)].g/8 + input1->getBuffer()[(j-1) * width + i].g/8 + input1->getBuffer()[(j+1) * width + i].g/8 + input1->getBuffer()[(j-1) * width + (i+1)].g/8 + input1->getBuffer()[j* width +(i+1)].g/8 + input1->getBuffer()[(j+1)* width + (i+1)].g/8;
				
				img.getBuffer()[j* width + i].b = input1->getBuffer()[(j-1)* width +(i-1)].b/8 + input1->getBuffer()[j* width +(i-1)].b/8 + input1->getBuffer()[(j+1) * width + (i-1)].b/8 + input1->getBuffer()[(j-1) * width + i].b/8 + input1->getBuffer()[(j+1) * width + i].b/8 +input1->getBuffer()[(j-1) * width + (i+1)].b/8 + input1->getBuffer()[j* width +(i+1)].b/8 + input1->getBuffer()[(j+1) * width + (i+1)].b/8;
			}

		}
	}

}


void Color::Execute() {
	
	int i, j;

	img.setValues(width, height);
	img.setBuffer(width, height);
	
	for(i = 0; i < img.getWidth(); i++) {
		for(j = 0; j < img.getHeight(); j++) {
		       img.getBuffer()[j* width + i].r = red;
	               img.getBuffer()[j* width + i].g = green;
		       img.getBuffer()[j* width + i].b = blue;
		 }
	}
	
}


void Color::Update() {
	Execute();
}


void CheckSum::OutputCheckSum(const char *filename) {

	FILE *f = fopen(filename, "w");
	int i,j;
	int width = input1->getWidth();
	int height = input1->getHeight();
	unsigned char red = 0;
	unsigned char blue = 0;
	unsigned char green = 0;
	
	for(i = 0; i < input1->getWidth(); i++) {
		for(j = 0; j < input1->getHeight(); j++) {
			red += input1->getBuffer()[j * width + i].r;
			blue += input1->getBuffer()[j * width + i].b;
			green += input1->getBuffer()[j * width + i].g;
		}
	}
	fprintf(f, "CHECKSUM: %d, %d, %d\n", red, green, blue);
	fclose(f);
}

