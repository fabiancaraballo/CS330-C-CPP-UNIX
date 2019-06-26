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

typedef struct {
	
	double x;
	double y;
	double radius;
} Circle;

typedef struct {

	double pt1X;
	double pt2X;
	double minY;
	double maxY;
} Triangle;

typedef struct {

	double minX;
	double maxX;
	double minY;
	double maxY;

} Rectangle;



