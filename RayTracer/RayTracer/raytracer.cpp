#include <fstream>
#include <cmath>

struct Vec {
	double x, y, z;
	Vec() { x = y = z = 0; }
	Vec(double a, double b, double c) { x = a, y = b, z = c; }
	Vec operator + (const Vec& v) const { return Vec(x + v.x, y + v.y, z + v.z); }
	Vec operator - (const Vec& v) { return Vec(x - v.x, y - v.y, z - v.z); }
	Vec operator * (double d) { return Vec(x*d, y*d, z*d);}
	Vec operator / (double d) { return Vec(x/d, y/d, z/d);}
	Vec GetNormalizedVector {double magnitude = sqrt(x*x+y*y+z*z); return Vec(x/magnitude, y/magnitude, z/magnitude);}

};

double dot(Vec x, Vec y) {return (x.x * y.x + x.y * y.y);}

struct Ray {
	Vec origin;
	Vec direction;
	Ray(Vec i, Vec j) { origin = i, direction = j; }
};

struct Color {
	double r, g, b;
	Color() {r = g = b = 0; }
	Color(double i, double j, double k) { r=i,g=j,b=k; }
	Color operator * (double d) {return Color(r*d, g*d, b*d);}
};

abstract class Shape {
protected:
	Vec Center;
public:
	bool intersect(Ray ray, double &t);
	Vec GetNormal(Vec point);
};

class Sphere {
public:
	Vec center;
	double radius;	//radius
	Sphere(Vec i, double j) { center = i, radius = j; }
	
	GetNormal(Vec pointOfIntersection){(center-pointOfIntersection)/radius;}

	//pass in t as intersection distance
	bool intersect(Ray ray, double &t) {
		Vec O = ray.origin;
		Vec D = ray.direction;
		//ray from pixel position to sphere center
		Vec originToSphere = center - O;
		//find projection of oc onto d to get leg of triangle from pixel toward sphere
		double projection = dot(originToSphere, D);
		//if it is negative, the vectors point in opposite directions and there is no intersection
		if (projection < 0) { return false; }
	
		//get the length squared of the other leg of the triangle from center out to ray path using pythagoras thrm
		double oppositeLegSq = dot(originToSphere, originToSphere) - projection*projection;

		//if leg is bigger than radius, there is no intersection
		if (oppositeLegSq > radius * radius) { return false; }
		//find the intersection point with trig using radius of sphere as hypotenuse 
		double adjacentLegInSphere = sqrt(radius*radius - oppositeLegSq);

		float intersectdistance1 = projection - adjacentLegInSphere;
		float intersectdistance2 = projection + adjacentLegInSphere;
		return true;
	}
};

int main()

{
	//image dimensions
	const int W = 500;
	const int H = 500;

	Color White = Color(255, 255, 255);
	Color Black = Color(0, 0, 0);

	Sphere sphere(Vec(W / 2, H / 2, 50), 20);

	std::ofstream out("out.ppm");
	out << "P3\n" << W << ' ' << H << ' ' << "255\n";

	Color Pixel_Color_Array[H][W];

	//iterate through pixels
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			//send ray through each pixel using a forward vector
			Ray ray(Vec(x, y, 0), Vec(0, 0, 1));

			double t = 20000;

			if (sphere.intersect(ray, t))
			{
				Pixel_Color_Array[y][x] = White;
			}

			out << Pixel_Color_Array[y][x].r << std::endl;
			out << Pixel_Color_Array[y][x].g << std::endl;
			out << Pixel_Color_Array[y][x].b << std::endl;


		}
	}
	return 0;
}