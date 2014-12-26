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
#include <vector>
#include <algorithm>
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

struct linestruct
{
    int x1,y1,x2,y2;
    linestruct(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};


vector<pair<int,int> > clicks;
vector<linestruct> linequeue;
vector<pair<int,int> > allPoints;
void handleButton(int button, int state, int x, int y)
{
    //FLIP Y!!!!!!
    if(state ==  GLUT_UP)
    {
	y = 800-y;
	//cerr << x<< " " << y << endl;
	clicks.push_back(pair<int,int>(x,y));
	allPoints.push_back(pair<int,int>(x,y));
	if(clicks.size()>1)
	{
	    //push something onto the draw queue
	    //linestruct l(clicks[0].first, clicks[0].second, clicks[1].first, clicks[1].second);
	    linestruct l(clicks[clicks.size()-2].first,
			 clicks[clicks.size()-2].second,
			 clicks[clicks.size()-1].first,
			 clicks[clicks.size()-1].second);
	    linequeue.push_back(l);
	    //clicks.clear();
	}


	glutPostRedisplay();
    }
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
	    renderPixel((x1+i),(y1+(slope*i)),r,g,b);
	}
    }
    else if(slope > 0)
    {

	int n=y2-y1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel(x1+(1/slope)*i,(y1+i),r,g,b);
	}
	
    }
    else if(slope < -1)
    {
	int n=y1-y2;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel(x1-(1/slope)*i,(y1-i),r,g,b);
	}	
    }
    else
    {
	int n = x2-x1;
	for(unsigned i = 0; i < n; i++)
	{
	    renderPixel((x1+i),(y1+(slope*i)),r,g,b);
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

bool myfunction (pair<int,int> i,pair<int,int>j) { return (i.second<j.second); }
void drawTriangle(pair<int,int> v1, pair<int,int> v2, pair<int, int> v3,
		  float r=1.0f, float g=1.0f, float b=1.0f)
{
    //determine lowest y in the triangle
    vector<pair<int,int> > sorted;
    sorted.push_back(v1);
    sorted.push_back(v2);
    sorted.push_back(v3);
    sort(sorted.begin(), sorted.end(),myfunction);
    //determine slope from the lowest pixel to the other pixels
    float m1 = sorted[0].second - sorted[2].second;
    m1 = m1 / (sorted[0].first - sorted[2].first);
    float m2 = sorted[0].second - sorted[1].second;
    m2 = m2 / (sorted[0].first - sorted[1].first);
    float m3 = sorted[2].second - sorted[1].second;
    m3 = m3 / (sorted[2].first - sorted[1].first);
    float x1 = sorted[0].first;
    float x2 = sorted[0].first;
    cout << m1 << endl;
    cout << m2 << endl;
    cout << m3 << endl;
    for(unsigned y = sorted[0].second; y <= sorted[1].second; y++)
    {

	//y values
	DDA(x1, y, x2, y,r,g,b);
	    
	x1 += 1.0f/m1;
	x2 += 1.0f/m2;

    }
    x1 = sorted[2].first;
    x2 = sorted[2].first;
    for(unsigned y = sorted[2].second; y >= sorted[1].second; y--)
    {

	//y values
	DDA(x1, y, x2, y,r,g,b);
	    
	x1 -= 1.0f/m1;
	x2 -= 1.0f/m3;

    }	
}


void GL_render()
{
    //glClearColor( 0.2f, 0.2f, 0.5f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT);



    if(allPoints.size()>2)
    {
	//drawTriangle(allPoints[0], allPoints[1], allPoints[2], 1.0,0.5,0.4);
	
	for(int i=2 ; i < allPoints.size(); i+= 3)
	{
	    float r = (float)(rand()%100)/100;
	    float b = (float)(rand()%100)/100;
	    float g = (float)(rand()%100)/100;
	    drawTriangle(allPoints[i-2], allPoints[i-1], allPoints[i], r,b,g);
	}
    }
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
    glutMouseFunc(handleButton);
    glutMainLoop();

    return 0;
}


