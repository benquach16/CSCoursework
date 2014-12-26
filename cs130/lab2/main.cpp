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
	/*
	if(clicks.size()>2)
	{
	    //push something onto the draw queue
	    linestruct l(clicks[1].first, clicks[1].second, clicks[2].first, clicks[2].second);
	    linequeue.push_back(l);
	    clicks.clear();
	    }*/

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


int binomialCoef(unsigned int n, const unsigned int k)
{
    int r = 1;

    if(k > n)
        return 0;

    for(int d = 1; d <= k; d++)
    {
        r *= n--;
        r /= d;
    }

    return r;
}

void drawBezierGen()
{
    /*
    vector<int> Xs;
    vector<int> Ys;
    int x = linequeue[0].x1;
    int y = linequeue[0].y1;
    float Lx, Ly;
    for(int n = 0; n < 10; n++)
    {
	for(int i = n; i < linequeue.size(); i++)
	{
	    Xs.push_back(linequeue[i].x2);
	    Ys.push_back(linequeue[i].y2);
	    Lx += calculateBezierX(Xs);
	    Ly += calculateBezierY(Ys);
	}

	DDA(x, y, Lx, Ly);
	x = Lx;
	y = Lx;
	Xs.clear();
	Ys.clear();
    }
    */

    int x = linequeue[0].x1;
    int y = linequeue[0].y1;
    int x0;
    int y0;
    //allPoints.push_back(allPoints[allPoints.size()-1]);
    float t = 0.0f;
    for(int i = 0; i < 200; i++)
    {
	t+= 1.0f/200;
	x0 = y0 = 0;
	
	for(int j = 0; j < allPoints.size(); j++)
	{
	    
	
            x0 += (binomialCoef(allPoints.size()-1, j) * pow(1 - t, (float)allPoints.size()-1 - j) * pow(t, j) * allPoints[j].first);
            y0 += (binomialCoef(allPoints.size()-1, j) * pow(1 - t, (float)allPoints.size()-1 - j) * pow(t, j) * allPoints[j].second);
	    
	    
        }


	DDA(x, y, x0, y0,0.5,1.0,0.5);
	x = x0;
	y = y0;
    }
    //DDA(x, y, allPoints[allPoints.size()-1].first, allPoints[allPoints.size()-1].second, 0.5,1.0,0.5);

}


void drawBezierCurve(int x1, int y1, int x2, int y2, int x3, int y3)
{
    //so we heff 3 lines
    
    /*
    float t = 0.1;
    for(unsigned i = 1; i < 10; i++)
    {
	t=1.0f/(float)i;
    float Lx = ((1-t)*((1-t)*x1 + t*x2)) + (t*((1-t)*x2, + t*x3));
    float Ly = ((1-t)*((1-t)*y1 + t*y2)) + (t*((1-t)*y2, + t*y3));
    cerr << Lx << " " << Ly << endl;
    DDA(x1, y1, Lx, Ly);
    x1 = Lx;
    y1 = Ly;
    }
    */
    int x = x1;
    int y = y1;
    float t = 0.0f;
    for(unsigned i = 0; i < 10; i++)
    {
	//t=1.0f/(float)i;
	t+=1.0f/10.0f;
	float u = (1-t);
	float Lx = (u*(u*x1 + t*x2)) + (t*(u*x2 + t*x3));
	float Ly = (u*(u*y1 + t*y2)) + (t*(u*y2 + t*y3));
	//float Lx = (1 - t) * (1 - t) * x1 + (2 * (1 - t)) * t * x2 + t * t * x3;
	//float Ly = (1 - t) * (1 - t) * y1 + (2 * (1 - t)) * t * y2 + t * t * y3;
	cerr << Lx << " " << Ly << endl;
	DDA(x, y, Lx, Ly, 1.0, 0.5, 0.5);
	x = Lx;
	y = Ly;

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

    for(unsigned i = 0; i < linequeue.size(); i++)
    {
	DDA(linequeue[i].x1, linequeue[i].y1, linequeue[i].x2, linequeue[i].y2);
    }
    /*
    if(linequeue.size() > 1)
    {
	drawBezierCurve(linequeue[0].x1, linequeue[0].y1, linequeue[0].x2, linequeue[0].y2, linequeue[2].x2, linequeue[2].y2);
	}*/
    if(linequeue.size() > 1)
    {
	drawBezierGen();
	for(int i = 2; i < allPoints.size(); i+=2)
	{
	    drawBezierCurve(allPoints[i-2].first, allPoints[i-2].second, 
			    allPoints[i-1].first, allPoints[i-1].second,
			    allPoints[i].first, allPoints[i].second);
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


