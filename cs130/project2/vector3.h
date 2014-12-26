#ifndef _VECTOR3_H_
#define _VECTOR3_H_

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3() : x(0.f), y(0.f), z(0.f)
    {
    }
    
	Vector3(const float &x, const float &y, const float &z) : x(x), y(y), z(z)
	{
	}
	    Vector3 operator-(const Vector3 &rhs)
	    {
		return Vector3(x - rhs.x,
			       y - rhs.y,
			       z - rhs.z);
	    }

	    Vector3 operator*(const Vector3 &rhs) const
	    {
		return Vector3(x * rhs.x,
			       y * rhs.y,
			       z * rhs.z);
	    }
	    Vector3 operator*(const float scalar) const
	    {
		return Vector3(x * scalar,
			       y * scalar,
			       z * scalar);
	    }
	    Vector3 operator+(const Vector3 &rhs)
	    {
		return Vector3(x + rhs.x,
			       y + rhs.y,
			       z + rhs.z);
	    }
	    Vector3 operator+=(const Vector3 &rhs)
	    {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	    }
	    Vector3 operator-=(const Vector3 &rhs)
	    {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	    }

	    Vector3 operator/=(float scalar)
	    {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	    }
	    bool operator==(const Vector3 &rhs)
	    {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	    }


	    Vector3 crossProduct(const Vector3 &rhs) const
	    {
		//find determinant for vector
		float i = (y * rhs.z) - (z * rhs.y);
		float j = (z * rhs.x) - (x * rhs.z);
		float k = (x * rhs.y) - (y * rhs.x);
		return Vector3(i,j,k);
	    }
	    
	    Vector3 inverse()
	    {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	    }
	    float magnitude() const
	    {
		return sqrt(x*x+y*y+z*z);
	    }
	    void normalize()
	    {
		*this /= magnitude();
	    }
	    

	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}	    
	float getDistanceFrom(const Vector3 & rhs) const
	{
	    float dx = rhs.x - x;
	    float dy = rhs.y - y;
	    float dz = rhs.z - z;
	    return sqrt(dx*dx+dy*dy+dz*dz);
	}
    
};

#endif
