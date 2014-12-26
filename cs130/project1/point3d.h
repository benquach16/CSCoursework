#ifndef _POINT3D_H_
#define _POINT3D_H_

class Point3D
{
public:
    float x;
    float y;
    float z;

    Point3D() : x(0.f), y(0.f), z(0.f)
    {
    }
    
	Point3D(const float &x, const float &y, const float &z) : x(x), y(y), z(z)
	{
	}
	    Point3D operator-(Point3D &rhs)
	    {
		return Point3D(x - rhs.x,
			       y - rhs.y,
			       z - rhs.z);
	    }

	    Point3D crossProduct(Point3D &rhs)
	    {
		//find determinant for vector
		float i = (y * rhs.z) - (z * rhs.y);
		float j = (z * rhs.x) - (x * rhs.z);
		float k = (x * rhs.y) - (y * rhs.x);
		return Point3D(i,j,k);
	    }

	    float dotProduct(Point3D &rhs)
	    {
		float ret = x*rhs.x + y*rhs.y + z*rhs.z;
		return ret;
	    }

	    
    
};

#endif
