// Name:  Ben Quach
// Quarter, Year: 2014 Fall
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "point2d.h"
#include "point3d.h"
#include "color.h"


using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


vector<Point3D> all3DPoints;
vector<int> indices;
Point3D center;
float rotationAmountY = 0.0f;
float rotationAmountX = 0.0f;
float scale = 1.0f;
bool wireframe = false;
int oldX = 0;
int oldY = 0;
Color framebuffer[800][800]; //not useful for now but if we want to do lighting or postprocessing this will be useful 
int zbuffer[800][800];

//IMPORTANT TODO: MAKE THIS INTO LIKE A CLASS OR GIVE IT A PROPER NAMESPACE
//IF WE'RE GOING TO MAKE A SOFTWARE RENDERER DONT JUST HAVE FUNCTIONS FLOATING
//IN THE GLOBAL NAMESPACE. A CLASS IS NICE BUT STRAIGHT C IS FASTER

void clearFrameBuffer()
{
    /*
    for(unsigned i = 0; i < 800; i++)
    {
	for(unsigned j = 0; j < 800; j++)
	{
	    framebuffer[i][j].r = 0.f;
	    framebuffer[i][j].g = 0.f;
	    framebuffer[i][j].b = 0.f;
	    
	}
	} */
    memset(&framebuffer, 0, sizeof(framebuffer));
}

void renderFrameBuffer()
{
    glBegin(GL_POINTS);
    for(unsigned i = 0; i < 800; i++)
    {
	for(unsigned j = 0; j < 800; j++)
	{
	    float r = framebuffer[i][j].r;
	    float g = framebuffer[i][j].g;
	    float b = framebuffer[i][j].b;

	    glColor3f(r, g, b);

	    glVertex2f(i,j);
	}
    }
    glEnd();
}

void clearZBuffer()
{
    memset(&zbuffer, -10000, sizeof(zbuffer));
    /*
    for(unsigned i = 0; i < 800; i++)
    {
	for(unsigned j = 0; j < 800; j++)
	{
	    
	    zbuffer[i][j] = -10000;

	}
	}*/
}

void renderPixel(int x, int y, int z = 1, float r = 1.0, float g = 1.0, float b = 1.0)
{
    if( x < 800 && y < 800 && x > -1 && y > -1)
    {
	//make sure our z is the best first before rendering
	if(zbuffer[x][y] <= z)
	{
	    glBegin(GL_POINTS);

	    glColor3f(r, g, b);
	    glVertex2f(x,y);
	    zbuffer[x][y] = z;
	    glEnd();
	}
    }   
    
}



//Use the left and right mouse buttons to rotate
void handleButton(int button, int state, int x, int y)
{
    //FLIP Y!!!!!!
    

    if(state == GLUT_UP)
    {
	if(button == GLUT_LEFT_BUTTON)
	{
	    rotationAmountY += 0.1f;
	    glutPostRedisplay();
	}
	else
	{
	    rotationAmountX += 0.1f;
	    glutPostRedisplay();
	}
    }
}

//use the WASD keys to pan the view around
//Q for wireframe
//Z and X to zoom in and out
void handleKey(unsigned char key, int x, int y)
{
    if(key == 97)
    {
	center.x -= 10;
	for(int i = 0; i < all3DPoints.size(); i++)
	{
	    all3DPoints[i].x -=10;
	}

    }
    if(key == 115)
    {
	center.y -= 10;
	for(int i = 0; i < all3DPoints.size(); i++)
	{
	    all3DPoints[i].y -=10;
	}

    }
    if(key == 100)
    {
	center.x += 10;
	for(int i = 0; i < all3DPoints.size(); i++)
	{
	    all3DPoints[i].x +=10;
	}

    }
    if(key == 119)
    {
	center.y += 10;
	for(int i = 0; i < all3DPoints.size(); i++)
	{
	    all3DPoints[i].y +=10;
	}

    }
    if(key == 113)
    {
	wireframe = !wireframe;
    
    }
    if(key == 120)
    {
	if(scale < 5)
	    scale+=0.1;

    }
    if(key == 122)
    {
	if(scale > 0.5)
	    scale -= 0.1;
    }
    glutPostRedisplay();
}


void DDA(int x1,int y1,int x2,int y2, float r = 1.0, float g = 1.0, float b = 1.0)
{
    //draw line betweeen points
    if(x1>x2)
    {
	int t = x1;
	x1=x2;
	x2=t;
	t=y1;
	y1=y2;
	y2=t;
    }

    float slope = y2 - y1;
    slope = slope/(x2-x1);
    //cerr << slope << endl;
    if(slope <= 1 && slope > 0)
    {
	int n = x2-x1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel((x1+i),(y1+(slope*i)),255,r,g,b);
	}
    }
    else if(slope > 0)
    {

	int n=y2-y1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel(x1+(1/slope)*i,(y1+i),255,r,g,b);
	}
	
    }
    else if(slope < -1)
    {
	int n=y1-y2;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel(x1-(1/slope)*i,(y1-i),255,r,g,b);
	}	
    }
    else
    {
	int n = x2-x1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel((x1+i),(y1+(slope*i)),255,r,g,b);
	}
    }
}



void OBJParse(const char* filename)
{
    ifstream file(filename);
    //fuck errors
    //if they exist we dont care
    int numPoints;
    int numTris;
    file >> numPoints;
    file >> numTris;
    //we need to calculate the center point of the 3d model
    //how do we do this?
    float allXs = 0.f;
    float allYs = 0.f;
    float allZs = 0.f;
    for(unsigned i = 0; i < numPoints; i++)
    {
	//3 parts of a vertex ofc
	float x, y, z;
	file >> x >> y >> z;
	allXs += x;
	allYs += y;
	allZs += z;
	Point3D p(x,y,z);
	//cerr << x << " " << y << " " << z << endl;
	all3DPoints.push_back(p);
    }
    for(unsigned i = 0; i < numTris;i++)
    {
	int x1,x2,x3;
	file >> x1 >> x2 >> x3;
	indices.push_back(x1);
	indices.push_back(x2);
	indices.push_back(x3);
    }
    allXs /= all3DPoints.size();
    allYs /= all3DPoints.size();
    allZs /= all3DPoints.size();
    center = Point3D(allXs,allYs,allZs);
}


//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // ...
    // Complete this function
    // ...
    glutCreateWindow("CS 130 - BEN QUACH");
    // The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
    // For the purposes of this lab, this is set to the number of pixels
    // in each dimension.
    glMatrixMode(GL_PROJECTION_MATRIX);
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    clearFrameBuffer();
    clearZBuffer();
}



//this functions hella fucked unfuck it now
bool myfunction (Point3D i, Point3D j) { return (i.y<j.y); }
void drawTriangle(const vector<Point3D> &sorted, Point3D &plane,
		  float r=1.0f, float g=1.0f, float b=1.0f)
{


    //determine slope from the lowest pixel to the other pixels
    float m1 = sorted[0].y - sorted[2].y;
    m1 = m1 / (sorted[0].x - sorted[2].x);
    float m2 = sorted[0].y - sorted[1].y;
    m2 = m2 / (sorted[0].x - sorted[1].x);
    float m3 = sorted[2].y - sorted[1].y;
    m3 = m3 / (sorted[2].x - sorted[1].x);
    float x1 = sorted[0].x;
    float x2 = sorted[0].x;
    float c = 0.f;
    c+= plane.x * sorted[0].x;
    c+= plane.y * sorted[0].y;
    c+= plane.z * sorted[0].z;

    int yMax = (sorted[1].y + 0.5);
    //cerr <<yMax<<endl;
    for(int y = sorted[0].y; y <= yMax; y++)
    {
	//cerr << y << endl;
	//y values
	//DDA(x1, y, x2, y,r,g,b);
	//dont use dda so we can input z values
	int max,min;
	//round up
	if(x2>x1)
	{
	    max = (int)(x2+0.5);
	    min = x1;
	}
	else
	{
	    max = (int)(x1+0.5);
	    min = x2;
	}
	

	for(int i = min; i < max; i++)
	{
	    //calculate z of this point meow
	    float z = (c-(plane.x*i)-(plane.y*y))/plane.z;
	    //cerr << z << endl;
	    renderPixel(i, y,z ,r,g,b);
	}

	x1 += 1.0f/m1;
	x2 += 1.0f/m2;
	
    }
    x1 = sorted[2].x;
    x2 = sorted[2].x;
    
    for(int y = sorted[2].y; y >= sorted[1].y; y--)
    {

	//y values
	//DDA(x1, y, x2, y,r,g,b);


	int max,min;
	//round up
	if(x2>x1)
	{
	    max = (int)(x2+0.5);
	    min = x1;
	}
	else
	{
	    max = (int)(x1+0.5);
	    min = x2;
	}

	for(int i = min; i < max; i++)
	{
	    //determine z of this point
	    //todo speed this the fuck up
	    float z = (c-(plane.x*i)-(plane.y*y))/plane.z;
	    //cerr << z << endl;
	    renderPixel(i, y,z ,r,g,b);
	}

	x1 -= 1.0f/m1;
	x2 -= 1.0f/m3;

    }	
}


//draw 2d triangle from 3d triangle
void project3Dto2D(Point3D &v1, Point3D &v2, Point3D &v3,
		   float r = 1.0, float g = 1.0, float b = 1.0)
{
    //cerr << p3.x << " " << p3.y<<endl;
    //now we have to find the equation of the plane
    vector<Point3D> sorted;
    sorted.push_back(v1);
    sorted.push_back(v2);
    sorted.push_back(v3);
    sort(sorted.begin(), sorted.end(),myfunction);    


    //get coefficients for plane equation
    Point3D vector1 = sorted[2] - sorted[0];
    Point3D vector2 = sorted[1] - sorted[0];
    Point3D cProd = vector1.crossProduct(vector2);

    //use this to find z
    //backface culling
    if(!wireframe)
    {
	//assuming this normalizaiton works
	if((cProd.x + cProd.y + cProd.z))
	    drawTriangle(sorted,cProd,r,g,b);

    }
    else
    {
	//draw 3 lines
	DDA(sorted[0].x,sorted[0].y,sorted[1].x,sorted[1].y);
	DDA(sorted[0].x,sorted[0].y,sorted[2].x,sorted[2].y);
	DDA(sorted[2].x,sorted[2].y,sorted[1].x,sorted[1].y);
    }
}

//self explanitory
void matrixMultiply(float *ret, float *m1, float *m2)
{


    for(int row = 0; row < 4; row++)
    {
	for(int col = 0; col <= 12; col+=4)
	{
	    for(int inner = 0; inner <4; inner++)
	    {
		ret[row+col] += m1[row+(inner*4)] * m2[col+inner];
	    }
	}
    }
}

//applies tranformation matrices to a point
Point3D transformPoint(Point3D p)
{
    //transform point by transformation matrix
    float coordinates[4] = {p.x,p.y,p.z,1};
    //matrix is [16]
    float s = sin(rotationAmountY);
    float c = cos(rotationAmountY);
    float s2 = sin(rotationAmountX);
    float c2 = cos(rotationAmountX);
    //transform to origin first
    coordinates[0] -= center.x;
    coordinates[1] -= center.y;
    coordinates[2] -= center.z;


    //if we want multiple rotations we have to multiply the matrix
    float m1[16] = {
	 c,0    ,s      ,0,
	 0      ,1,0      ,0,
	-s      ,0    ,c,0,
	 0,0,0,1};

    float m2[16] = {
	1,0,0,0,
	0,c2,s2,0,
	0,-s2,c2,0,
	0,0,0,1};

    float ret[16] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0};

    matrixMultiply(ret, m1,m2);

    float m3[16]= {
	scale,0,0,0,
	0,scale,0,0,
	0,0,scale,0,
	0,0,0,1};


    float m[16] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0}; 
    matrixMultiply(m, ret, m3);
    
    float resultant[4] = {0,0,0,1};
    for(int i = 0; i < 4; i++)
    {
	resultant[0] += m[i] * coordinates[i];
    }
    for(int i = 0; i < 4; i++)
    {
	resultant[1] += m[4+i] * coordinates[i];
    }
    for(int i = 0; i < 4; i++)
    {
	resultant[2] += m[8+i] * coordinates[i];
    }
    for(int i = 0; i < 4; i++)
    {
	resultant[3] += m[12+i] * coordinates[i];
    }


    resultant[0] += center.x;
    resultant[1] += center.y;
    resultant[2] += center.z;

    p.x = resultant[0];
    p.y = resultant[1];
    p.z = resultant[2];

    return p;
}

void GL_render()
{
    //glClearColor( 0.2f, 0.2f, 0.5f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT);
    clearZBuffer();
    //clearFrameBuffer();

    if(indices.size()>2)
    {
	for(int i = 2; i < indices.size(); i+=3)
	{

	    float r = (float)i / (indices.size());
	    float b = (float)i / (indices.size());
	    float g = (float)i / (indices.size());
	    Point3D p1 = transformPoint(all3DPoints[indices[i-2]]);
	    Point3D p2 = transformPoint(all3DPoints[indices[i-1]]);
	    Point3D p3 = transformPoint(all3DPoints[indices[i]]);	    
	    //cerr << indices[i-2]<< " " << indices[i-1]<< " " <<indices[i] << endl;
	    project3Dto2D(p1,
			  p2,
			  p3,
			  r,g,b);
	}
    }

    //renderFrameBuffer();
/*
    for(unsigned i = 0; i < 50; i++)
    {
	renderPixel(100+i,100+i);
    }
    
    glBegin(GL_TRIANGLES);
    glVertex2f(10,10);
    glVertex2f(10,30);
    glVertex2f(40,10);
    glEnd();*/
    glutSwapBuffers();
}



//A recap of the controls,
//Mouse buttons for rotation
//WASD for panning
//Z and X for zoom
//Q for wireframe
int main(int argc, char** argv)
{	
    GLInit(&argc, argv);
    if(argc > 1)
    {
	OBJParse(argv[1]);
    }
    glutDisplayFunc(GL_render);
    glutMouseFunc(handleButton);
    glutKeyboardFunc(handleKey);
    glutMainLoop();

    return 0;
}


