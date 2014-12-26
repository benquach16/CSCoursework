#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "vector3.h"


class Vertex
{
public:
    Vector3 position;
    Vector3 normal;

    Vertex();
    Vertex(Vector3 position) : position(position) {}
    Vertex(Vector3 position, Vector3 normal) : position(position), normal(normal) {}
    
};

#endif

