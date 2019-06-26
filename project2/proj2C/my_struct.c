/* This file should contain the 9 functions defined in prototypes.h */

#include <math.h>
#include <prototypes.h>

void InitializeCircle(Circle *c, double radius, double originX, double originY){

	c->radius = radius;
	c->x = originX;
	c->y = originY;
}
void InitializeRectangle(Rectangle *r, double minX, double maxX, double minY, double maxY){

	r->minX = minX;
	r->maxX = maxX;
	r->minY = minY;
	r->maxY = maxY;

}

void InitializeTriangle(Triangle *t, double pt1X, double pt2X, double minY, double maxY){

	t->pt1X = pt1X;
	t->pt2X = pt2X;
	t->minY = minY;
	t->maxY = maxY;
}


double GetCircleArea(Circle *circ) {

	double pi = 3.14159;
	double area = (pi * circ->radius * circ->radius);
	return area;
}

double GetRectangleArea(Rectangle *rec) {
	
	double area = (rec->maxX - rec->minX) * (rec->maxY - rec->minY);
	return area;
}

double GetTriangleArea(Triangle * trgle) {
	
	double area = ((trgle->pt2X - trgle->pt1X) * (trgle->maxY - trgle->minY)) / 2;
	return area;
}

void GetCircleBoundingBox(Circle *circ, double *bbox) {
	bbox[0] = (circ->x - circ->radius);
	bbox[1] = (circ->x + circ->radius);
	bbox[2] = (circ->y - circ->radius);
	bbox[3] = (circ->y + circ->radius);
}

void GetRectangleBoundingBox(Rectangle *rec, double *bbox) {
	bbox[0] = rec->minX; 
	bbox[1] = rec->maxX; 
	bbox[2] = rec->minY; 
	bbox[3] = rec->maxY; 
}

void GetTriangleBoundingBox(Triangle *trgle, double *bbox) {
	bbox[0] = trgle->pt1X;
	bbox[1] = trgle->pt2X;
	bbox[2] = trgle->minY;
	bbox[3] = trgle->maxY;
}

