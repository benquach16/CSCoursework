#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    float r, g, b;
    Color(){}
    Color(float r, float g, float b) : r(r),b(b),g(g) {}
	Color operator*(float scalar)
	{
	    return Color(r*scalar, g*scalar, b*scalar);
	}

    
};

#endif
