// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include <iostream>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float VIEW_LEFT = 0.0;
const float VIEW_RIGHT = WINDOW_WIDTH;
const float VIEW_BOTTOM = 0.0;
const float VIEW_TOP = WINDOW_HEIGHT;
const float VIEW_NEAR = -400;
const float VIEW_FAR = 400;

// Retrieve random float
float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}

// A simple wrapper for store 3D vectors
struct Vector3
{
	float x;
	float y;
	float z;
    
	Vector3() : x(0.0), y(0.0), z(0.0)
	{}
    
	Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
	{}
    
	Vector3(const Vector3 & v)
    : x(v.x), y(v.y), z(v.z)
	{}
    
	Vector3 operator+(const Vector3 & rhs) const
	{ return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator-(const Vector3 & rhs) const
	{ return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator*(float rhs) const
	{ return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator/(float rhs) const
	{ return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3 operator+=(const Vector3 & rhs)
	{ x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3 operator-=(const Vector3 & rhs)
	{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3 operator*=(float rhs)
	{ x *= rhs; y *= rhs; z *= rhs; return *this; }
	Vector3 operator/=(float rhs)
	{ x /= rhs; y /= rhs; z /= rhs; return *this; }
    
	float magnitude() const
	{ return sqrt(x * x + y * y + z * z); }
	void normalize()
	{ *this /= magnitude(); }
	Vector3 normalized() const
	{ return *this / magnitude(); }
	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vector3 cross(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y,
                       z * rhs.x - x * rhs.z,
                       x * rhs.y - y * rhs.x);
	}
};

// A simple wrapper to store colors
struct Color3d
{
	float r;
	float g;
	float b;
	float a;
    
	Color3d()
    : r(0.0), g(0.0), b(0.0), a(1.0)
	{}
	Color3d(float r, float g, float b, float a = 1.0)
    : r(r), g(g), b(b), a(a)
	{}
};

void renderPixel(int x, int y, Color3d& color, float sz = 1.0)
{
	glPointSize(sz);
	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


struct Sphere
{
    Vector3 center;
    float radius;
    Color3d color;
    Sphere() : radius(1.0) {}
    Sphere(const Vector3& cent, const float& R, const Color3d& col)
    {
        if (R > 0.0) {radius = R;} else {radius = 1.0;}
        center = cent;  color = col;
    }
};

vector<Sphere> spheres;

void loadSpheres()
{
    /* TODO
     Add some spheres to the "spheres" vector.*/
    spheres.push_back(Sphere(Vector3(400,400,500),100,Color3d()));
    spheres.push_back(Sphere(Vector3(300,300,490),100,Color3d(0.0f,1.0f,0.0f,1.0f)));
}

struct Ray
{
    Vector3 origin;
    Vector3 direction;
    Ray() {Vector3 d(0.0, 0.0, 1.0);  direction = d;}
    Ray(const Vector3& o, const Vector3& dir)
    {
        origin = o;
        Vector3 d(0.0, 0.0, 1.0);
        float mag = dir.magnitude();
        if (mag > 0.0) {d = dir;}
        direction = d;
    }
};

bool rayIntersectsSphere(const Ray& ray, const Sphere& sphere, float* t_small = NULL, float* t_large = NULL)
{
    //Ray can be written origin + direction * t where t >= 0
    //Sphere can be written as (x - center.x)^2 + (y - center.y)^2 + (z - center.z)^2 = radius^2
    //Need to determine where these equations coincide.  If
    
    if (t_small != NULL) {*t_small = -1.0;} //These default values mean these values are invalid.
    if (t_large != NULL) {*t_large = -1.0;}
    
    /*
     TODO
     The ray is written as origin + direction * t where t >= 0.
     Write a function to solve for t_small <= t_large.  These are the different values of t
     for which the ray intersects the sphere.  These t-values are solutions to a quadratic equation
     which will have 0, 1, or 2 real solutions.  If there are 0 solutions, return false.
     If neither t_small nor t_large are >= 0, return false.  Otherwise, return true.
     */
    //get surface of sphere
    //check if ray intersects
    
    float a = ray.direction.magnitude();
    a = a * a;
    float b = (ray.direction*2).dot(ray.origin - sphere.center);
    float c = (ray.origin - sphere.center).magnitude();
    c = c*c;
    c -= (sphere.radius*sphere.radius);
    //std::cerr << c << std::endl;
    float discriminant = sqrt(b*b - 4*a*c);
    //std::cerr << discriminant << std::endl;
    if(isnan(discriminant))
	return false;
    if(t_small != NULL)
	*t_small = (-b - discriminant)/(2*a);
    if(t_large != NULL)
	*t_large = (-b + discriminant)/(2*a);

    //std::cerr<<*t_small<<std::endl;
    //std::cerr<<*t_large<<std::endl;
    return true;
}
//Returns -1 if no sphere should appear in pixel, otherwise returns index of sphere.
int pixelOn(float pixel_x, float pixel_y)
{
    Ray current(Vector3(pixel_x, pixel_y, 0.0), Vector3(0.0, 0.0, 1.0));
    int num_spheres = (int) spheres.size();
    float min = -1.0;
    int min_i = -1;
    for (int i = 0; i < num_spheres; i++)
    {
        /*
         TODO
         Fill this in.
         The loop should make min_i the index of the first sphere intersected by current ray.
         If none exists, min_i will stay = -1.  Use the float min to keep track of smallest
         nonnegative t-value.
         */
	float t_small;
	float t_large;
	
	if(rayIntersectsSphere(current, spheres[i], &t_small, &t_large))
	{
	    if(min == -1)
	    {
		min = t_small;
		min_i = i;
	    }
	    else
	    {
		if(t_small < min)
		{
		    min = t_small;
		    min_i = i;
		}
	    }
	}
    }
    return min_i;
}

void GLrender();

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab 7 - Enter Your Name");
	glutDisplayFunc(GLrender);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glOrtho(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, VIEW_NEAR, VIEW_FAR);
}

int main(int argc, char** argv)
{
	GLInit(&argc, argv);
    loadSpheres();
	glutMainLoop();
	return 0;
}

void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT; j++)
        {
            int which_sphere = pixelOn(i, 800 - j);
            if (which_sphere >= 0)
            {
                renderPixel(i, 800 - j, spheres[which_sphere].color);
            }
        }
    }
    
	glFlush();	
	glutSwapBuffers();
}

