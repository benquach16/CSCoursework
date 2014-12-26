#ifndef __FACE_H__
#define __FACE_H__


#include "vector3.h"
#include "color.h"
#include "vertex.h"
#include <vector>


class Face
{
public:

	Face(Vertex *v1, Vertex *v2, Vertex *v3) : 
	    v1(v1),v2(v2),v3(v3) {}
	Vertex *v1;
	Vertex *v2;
	Vertex *v3;
	int index1;
	int index2;
	int index3;
    Vector3 normal;

};

#endif

