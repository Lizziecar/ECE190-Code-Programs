#include <math.h>
#include <stdio.h>

typedef struct Point {
	double x;
	double y;
}; Point

double euclidean_dist(struct Point p1, struct Point p2) {
	return pow(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2), 0.5);
}

void change_point_to_origin(Point p) {
	p.x = 0;
	p.y = 0;
}

int main() {
	Point point1
	point1.x = 10.0;
	point1.y = 5.0;
	
	Point point2
	point2.x = 10.0;
	point2.y = 5.0;
	
	change_point_to_origin(Point p);
	//doesn't change the variable
	
	double result = euclidean_dist(point1, point2);
	fprintf(stdout, "%0.2f \n", result);
}