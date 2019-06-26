/* This file should contain your struct definitions for Circle, Triangle, and 
   Rectangle */

struct Rectangle
{
	        double minX, maxX, minY, maxY;
};

struct Circle
{
	        double x, y, radius;

};

struct Triangle
{
	        double pt1X, pt2X, minY, maxY;


};

enum ShapeType {
	Circle,
	Rectangle,
	Triangle
};

union ShapeUnion {
	struct Circle c;
	struct Triangle t;
	struct Rectangle r;
};

struct Shape;

struct FunctionTable
{
	
	double (*GetArea)(struct Shape *shape);
	void (*GetBoundingBox)(struct Shape *shape, double *bbox);

};


struct Shape
{
	/* add data members for Shape */
	union ShapeUnion uShape;
	enum ShapeType type;
	struct FunctionTable ft;
};
