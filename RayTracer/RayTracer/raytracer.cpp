#include <fstream>
#include <cmath>

class Vec {
public:
	double x, y, z;
	Vec() { x = y = z = 0; }
	Vec(double a, double b, double c) { x = a, y = b, z = c; }
	Vec operator - (Vec v) { return Vec(x - v.x, y - v.y, z - v.z); }
};

double dot(Vec x, Vec y) {return (x.x * y.x + y.x * y.y);}

class Ray {
public:
	Vec o;	//origin
	Vec d;	//direction
	Ray(Vec i, Vec j) { o = i, d = j; }
};

class Sphere {
	Vec c;		//center
	double r;	//radius
	Sphere(Vec i, double j) { c = i, r = j; }
	bool intersect(Ray ray, double &t) {
		Vec o = ray.o;
		Vec d = ray.d;
		//ray from pixel position to sphere center
		Vec oc = o - c;
		//find projection of oc onto d to get leg of triangle form from pixel to sphere center
		double leg = dot(oc, d);
		if (leg < 0) { return false; }
		//get the length of the other leg of the triangle from center out to ray path using pythagoras thrm
		
		double disc = b*b - 4 * c;
		if (disc < 0) return false;
	}
};

int main()

{
	//image dimensions
	const int W = 500;
	const int H = 500;

	//iterate through pixels
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			//send ray through each pixel using a forward vector
			Ray ray(Vec(x, y, 0), Vec(0, 0, 1));

			if (sphere.intersect(ray));


		}
	}
}