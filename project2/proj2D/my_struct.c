/* This file should contain the 9 functions defined in prototypes.h */

#include <math.h>
#include <prototypes.h>


void InitializeCircle(struct Shape * shape, double radius, double originX, double originY){
	
	shape->type = Circle;
	shape->ft.GetArea = &GetCircleArea;
	shape->ft.GetBoundingBox = &GetCircleBoundingBox;
	shape->uShape.c.radius = radius;
	shape->uShape.c.x = originX;
	shape->uShape.c.y = originY;
	 
	
}
void InitializeRectangle(struct Shape * shape, double minX, double maxX, double minY, double maxY){

	shape->type = Rectangle;
	shape->ft.GetArea = &GetRectangleArea;
	shape->ft.GetBoundingBox = &GetRectangleBoundingBox;
	shape->uShape.r.minX = minX;
	shape->uShape.r.minY = minY;
	shape->uShape.r.maxX = maxX;
	shape->uShape.r.maxY = maxY;


}

void InitializeTriangle(struct Shape * shape, double pt1X, double pt2X, double minY, double maxY){

	shape->type = Triangle;
	shape->ft.GetArea = &GetTriangleArea;
	shape->ft.GetBoundingBox = &GetTriangleBoundingBox;
	shape->uShape.t.pt1X = pt1X;
	shape->uShape.t.pt2X = pt2X;
	shape->uShape.t.minY = minY;
	shape->uShape.t.maxY = maxY;

}


double GetCircleArea(struct Shape * shape) {

	double pi = 3.14159;
	shape->type == Circle;
	double rad = shape->uShape.c.radius;
	double area = (pi * rad * rad);
	return area;
}

double GetRectangleArea(struct Shape * shape) {
	
	shape->type == Rectangle;
	double width = shape->uShape.r.maxX - shape->uShape.r.minX;
	double height = shape->uShape.r.maxY - shape->uShape.r.minY;
	double area = width*height;;
	return area;
}

double GetTriangleArea(struct Shape * shape) {
	
	shape->type == Triangle;
	double base = shape->uShape.t.pt2X - shape->uShape.t.pt1X;
	double height = shape->uShape.t.maxY - shape->uShape.t.minY;
	double half = 0.5
	double area = half * base * height;
	return area;
}

void GetCircleBoundingBox(struct Shape * shape, double *bbox) {

	shape->type == Circle;
	bbox[0] = shape->uShape.c.x - shape->uShape.c.radius;
	bbox[1] = shape->uShape.c.x + shape->uShape.c.radius;
	bbox[2] = shape->uShape.c.y - shape->uShape.c.radius;
	bbox[3] = shape->uShape.c.y + shape->uShape.c.radius;


}

void GetRectangleBoundingBox(struct Shape * shape, double *bbox) {

	shape->type == Rectangle;
	bbox[0] = shape->uShape.r.minX; 
	bbox[1] = shape->uShape.r.maxX; 
	bbox[2] = shape->uShape.r.minY; 
	bbox[3] = shape->uShape.r.maxY; 
	

}

void GetTriangleBoundingBox(struct Shape * shape, double *bbox) {

	shape->type == Triangle;
	bbox[0] = shape->uShape.t.pt1X;
	bbox[1] = shape->uShape.t.pt2X;
	bbox[2] = shape->uShape.t.minY;
	bbox[3] = shape->uShape.t.maxY;



}

