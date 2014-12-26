// Name: 
// Quarter, Year: 
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{
    // ...
    // Complete this function
    // ...

    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2f(x, y);

    glEnd();
}

void circle(int x0, int y0, int radius)
{


    int x = radius;
    int y = 0;
    int radiusError = 1-x;

    while(x >= y)
    {   
	renderPixel(x + x0, y + y0);
	renderPixel(y + x0, x + y0);
	renderPixel(-x + x0, y + y0);
	renderPixel(-y + x0, x + y0);
	renderPixel(-x + x0, -y + y0);
	renderPixel(-y + x0, -x + y0);
	renderPixel(x + x0, -y + y0);
	renderPixel(y + x0, -x + y0);
	y++;
	if(radiusError < 0)
	{
	    radiusError += 2 * y + 1;
	}
	else
	{
	    x--;
	    radiusError += 2 * (y - x + 1);
	}

    }
}

void DDA(int x1,int y1,int x2,int y2, float r = 1.0, float g = 1.0, float b = 1.0)
{
    //draw line betweeen points

    float slope = y2 - y1;
    slope = slope/(x2-x1);
    //cerr << slope << endl;
    if(slope <= 1)
    {
	int n = x2 - x1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel((x1+i),(y1+(slope*i)),r,g,b);
	}
    }
    else
    {
	int n = y2 - y1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel(x1+(1/slope)*i,(y1+i),r,g,b);
	}
	
    }
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

}

void GL_render()
{
    //glClearColor( 0.2f, 0.2f, 0.5f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT);
    DDA(100,100,800,300);
    DDA(100,100,400,400);
    DDA(100,100,200,400);
    DDA(100,100,300,200);
    circle(400,400,100);
    circle(400,400,75);
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


int main(int argc, char** argv)
{	
    GLInit(&argc, argv);
    glutDisplayFunc(GL_render);

    glutMainLoop();

    return 0;
}


