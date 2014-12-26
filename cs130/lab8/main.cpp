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
#include <complex>
#include "color.h"
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float VIEW_LEFT = 0.0;
const float VIEW_RIGHT = WINDOW_WIDTH;
const float VIEW_BOTTOM = 0.0;
const float VIEW_TOP = WINDOW_HEIGHT;
const float VIEW_NEAR = -400;
const float VIEW_FAR = 400;
const int MAX_ITERS = 100;

double zoom = 1;
float moveX = 0;
float moveY = 0;
void GLrender();

void renderPixel(int x, int y, Color3d& color, float sz = 2.0)
{
	glPointSize(sz);
	glColor4f(color.r, color.g, color.b, 1.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}



void renderJuliaSet(double xmin, double xmax, double ymin, double ymax)
{

    double newRe, oldRe;
    double newIm, oldIm;
    double r = 0;
    double g = 0;
    double b = 1;
    Color3d color(r,g,b);
    for(int x = 0; x < WINDOW_WIDTH; x++)
    {
	for(int y = 0; y < WINDOW_HEIGHT;y++)
	{
	    newRe = (x - WINDOW_WIDTH/2) / (0.5 *zoom* WINDOW_WIDTH) + moveX;
	    newIm = (y - WINDOW_HEIGHT/2) / (0.5 *zoom* WINDOW_HEIGHT) + moveY;
	    int i;
	    for( i = 0; i < MAX_ITERS; i++)
	    {
		oldRe = newRe;
		oldIm = newIm;
		newRe = oldRe*oldRe -oldIm *oldIm -0.75;
		newIm = 2 * oldRe * oldIm + 0.12;
		
		if((newRe * newRe + newIm * newIm) > 4) break;
	    }
	    color.r = r;
	    color.g = g;
	    color.b = b;
	    color.rotateHue((double)i/MAX_ITERS*360);
	    renderPixel(x,y,color);
	}
    }
}

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

	glutMainLoop();
	return 0;
}

void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	renderJuliaSet(-2,2,-2,2);
    
	glFlush();	
	glutSwapBuffers();
}

