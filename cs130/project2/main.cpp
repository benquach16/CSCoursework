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
#include "vector3.h"
#include "color.h"
#include "face.h"
#include "ray.h"



using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;


vector<Vertex> all3DPoints;
//vector<Vector3> allNormals;
//vector<Vector3> vertexNormals;
vector<Face> faces;
Vector3 center;
float rotationAmountY = 0.0f;
float rotationAmountX = 0.0f;
float scale = 1.0f;
bool flat = false;
int oldX = 0;
int oldY = 0;
float specularCoefficient = 0.9;
Color framebuffer[800][800]; //not useful for now but if we want to do lighting or postprocessing this will be useful 
int zbuffer[800][800];
Color ambientLight(0.3,0.3,0.4);
Color diffuseLight(0.6,0.6,0.6);
Vector3 lightPos(100,400,-200);
Vector3 transformPoint(Vector3);
bool hitPolygon(Ray r, Face f, float &t_small);


void clearFrameBuffer()
{
    memset(&framebuffer, 0, sizeof(framebuffer));
}

float clamp(int f)
{
    return (float)f/255;
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
	    framebuffer[x][y] = Color(r,g,b);
	    glEnd();
	}
    }   
    
}

void renderPixel(int x, int y, float r = 1.0, float g = 1.0, float b = 1.0)
{

    //make sure our z is the best first before rendering

    glBegin(GL_POINTS);

    glColor3f(r, g, b);
    glVertex2f(x,y);

    glEnd();

    
}

//Defunct since we dont need user rotation anymore
void handleButton(int button, int state, int x, int y)
{

}

//use the WASD keys to pan the view around
//Q for wireframe
//Z and X to zoom in and out
void handleKey(unsigned char key, int x, int y)
{
    if(key == 'x')
    {
	//change from flat to phong
	flat = !flat;
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
	Vector3 p(x,y,z);
	//cerr << x << " " << y << " " << z << endl;
	all3DPoints.push_back(p);
    }
    for(unsigned i = 0; i < numTris;i++)
    {
	int x1,x2,x3;
	file >> x1 >> x2 >> x3;
	Face f = Face(&all3DPoints[x1],
		      &all3DPoints[x2],
		      &all3DPoints[x3]);
	f.index1 = x1;
	f.index2 = x2;
	f.index3 = x3;
	Vector3 vector1 = f.v3->position - f.v1->position;
	Vector3 vector2 = f.v2->position - f.v1->position;
	Vector3 cProd = vector1.crossProduct(vector2);	
	cProd.normalize();
	f.normal = cProd;
	faces.push_back(f);
    }
    allXs /= all3DPoints.size();
    allYs /= all3DPoints.size();
    allZs /= all3DPoints.size();
    center = Vector3(allXs,allYs,allZs);

    for(int i = 0; i < all3DPoints.size();i++)
    {
	//for each vertex get the avg of faces around it
	int numTris;

	for(int j = 0; j < faces.size(); j++)
	{
	    if(faces[j].index1 == i)
	    {
		numTris++;
		faces[j].v1->normal += faces[j].normal;
	    }
	    else if(faces[j].index2 == i)
	    {
		numTris++;
		faces[j].v2->normal += faces[j].normal;
	    }
	    else if(faces[j].index3 == i)
	    {
		numTris++;
		faces[j].v3->normal += faces[j].normal;
	    }
	}
	all3DPoints[i].normal.normalize();
	//cerr << all3DPoints[i].normal.x << " " << all3DPoints[i].normal.y << " " << all3DPoints[i].normal.z <<endl;
    }

    rotationAmountY -= 0.1f;
    rotationAmountX += 0.05f;

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

Vector3 reflectedRay(Vector3 ray, Vector3 normal)
{
    //Vector3 n = (normal * (2 * (ray.dot(normal))));
    //return ray - n;
    float f = ray.dot(normal);
    return ray - ((normal * f) * 2.0f);
}

//USE BARYCENTRIC INTERPOLATION
Vector3 getInterpolatedNormal(Face f, Vector3 P)
{
    //FIND BARYCENTRIC COORDINATES
    //AND GET THE AREA FOR EACH TRIANGLE
    //jesus
    Vector3 BA = f.v3->position - f.v1->position;
    Vector3 CA = f.v2->position - f.v1->position;
    Vector3 BP = f.v2->position - P;
    Vector3 CP = f.v3->position - P;
    Vector3 AP = f.v1->position - P;
    float areaABC = BA.crossProduct(CA).magnitude();
    //float areaPBC = f.normal.dot(BP.crossProduct(CP));
    //float areaPCA = f.normal.dot(CP.crossProduct(AP));
    //float areaPAB = f.normal.dot(AP.crossProduct(BP));
    float areaPBC = BP.crossProduct(CP).magnitude();
    float areaPCA = CP.crossProduct(AP).magnitude();
    float areaPAB = AP.crossProduct(BP).magnitude();
    
    float A = areaPAB/areaABC;
    float B = areaPBC/areaABC;
    float C = areaPCA/areaABC;    
    Vector3 normal;
    Vector3 v1 = f.v1->normal * B;
    Vector3 v2 = f.v2->normal * C;
    Vector3 v3 = f.v3->normal * A;

    normal = v1 + v2 + v3;
    normal.normalize();

    return normal;
}


void drawPhong(Face f, int i, int y, int c)
{
    float r,g,b;
    float z = (c-(f.normal.x*i)-(f.normal.y*y))/f.normal.z;
    Vector3 pixel(i,y,z);
    //cerr << z << endl;
    r = ambientLight.r;
    b = ambientLight.b;
    g = ambientLight.g;
    //compute lighting for this triangle
    //get normal we computed for this triangle
    //get the interpolated normal
    Vector3 viewerVector = pixel - Vector3(400,400,0);
    viewerVector.normalize();
    bool flipped=false;
    if(viewerVector.dot(f.normal) > 0)
    {
	f.normal.inverse();
	flipped = true;
    }
    Vector3 lightVector = lightPos - pixel;
    lightVector.normalize();
    Vector3 pixelNormal = getInterpolatedNormal(f, pixel);



    float d = lightVector.dot(pixelNormal);
    //d = abs(d);
    //d = 1-d;
    //calculate vector of light
    //use that we found d to calculate the new angle
    
    Vector3 reflectionVector;
    reflectionVector = reflectedRay(lightVector, f.normal);
    reflectionVector.normalize();
    float nDot = f.normal.dot(lightVector);
    Vector3 reflected(2 * f.normal.x * nDot - lightPos.x, 
		      2 * f.normal.y * nDot - lightPos.y, 2 * f.normal.z *nDot - lightPos.z);
    reflected.normalize();
    //find dot between 400,400,-400 and point

    
    float d2 = viewerVector.dot(reflected);

    d2 = pow(d2,50);

    r = (r * d * diffuseLight.r) + (specularCoefficient * d2) + 0.01;
    if(r > 1)
	r = 1;
    b = (b * d * diffuseLight.b) + (specularCoefficient * d2) + 0.01;
    if(b > 1)
	b = 1;
    g = (g * d * diffuseLight.g) + (specularCoefficient * d2) + 0.01;
    if(g > 1)
	g= 1;

    renderPixel(i, y,z ,r,g,b);
}

void drawFlat(Face f, int i, int y, int c)
{
    float r,g,b;
    float z = (c-(f.normal.x*i)-(f.normal.y*y))/f.normal.z;
    Vector3 pixel(i,y,z);
    //cerr << z << endl;
    r = ambientLight.r;
    b = ambientLight.b;
    g = ambientLight.g;
    Vector3 lightVector = center - lightPos;
    lightVector.normalize();
    float d = f.normal.dot(lightVector);
    d = abs(d);
    r = r * d * diffuseLight.r;
    if(r > 1)
	r = 1;
    g = g * d * diffuseLight.g;
    if(g > 1)
	g = 1;
    b = b * d * diffuseLight.b;
    if(b > 1)
	b = 1;
    renderPixel(i, y,z ,r,g,b);
}

//this functions hella fucked unfuck it now
bool myfunction (Vector3 i, Vector3 j) { return (i.y<j.y); }
void drawTriangle(const vector<Vector3> &sorted, Face f,
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
    c+= f.normal.x * sorted[0].x;
    c+= f.normal.y * sorted[0].y;
    c+= f.normal.z * sorted[0].z;

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
	    if(!flat)
		drawPhong(f,i,y,c);
	    else
	    {
		//draw flat
		drawFlat(f,i,y,c);
	    }
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
	    if(!flat)
		drawPhong(f,i,y,c);
	    else
	    {
		//draw flat
		drawFlat(f,i,y,c);
	    }
	}

	x1 -= 1.0f/m1;
	x2 -= 1.0f/m3;

    }	
}


//draw 2d triangle from 3d triangle
void project3Dto2D(Face f,
		   float r = 1.0, float g = 1.0, float b = 1.0)
{
    //cerr << p3.x << " " << p3.y<<endl;
    //now we have to find the equation of the plane
    vector<Vector3> sorted;
    sorted.push_back(f.v1->position);
    sorted.push_back(f.v2->position);
    sorted.push_back(f.v3->position);
    sort(sorted.begin(), sorted.end(),myfunction);    


    //get coefficients for plane equation
    Vector3 vector1 = sorted[2] - sorted[0];
    Vector3 vector2 = sorted[1] - sorted[0];
    Vector3 cProd = vector1.crossProduct(vector2);
    
    Vector3 t = cProd - center;

    //use this to find z
    //backface culling
    //assuming this normalizaiton works

	drawTriangle(sorted,f,r,g,b);
    

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
Vector3 transformPoint(Vector3 p)
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


float findDeterminant(float *m)
{
    //assuming 3x3 matrix.
    return (m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7] - 
	    m[6] * m[4] * m[2] - m[7] * m[5] * m[0] - m[8] * m[3] * m[1]);
}

bool hitPolygon(Ray r, Face f, float &t_small)
{
    //see if ray hit face
    //get the plane equation
    //check if ray intersects plane first to find p

    Vector3 a = f.v1->position;
    Vector3 b = f.v2->position;
    Vector3 c = f.v3->position;

    Vector3 Eb = b - a;
    Vector3 Ec = c - a;

    float T[9] = {
	-Eb.x, -Ec.x, (a.x - r.origin.x),
	-Eb.y, -Ec.y, (a.y - r.origin.y),	
	-Eb.z, -Ec.z, (a.z - r.origin.z) };


    float C[9] = {
	-Eb.x, (a.x - r.origin.x), r.direction.x,
	-Eb.y, (a.y - r.origin.y), r.direction.y,
	-Eb.z, (a.z - r.origin.z), r.direction.z };    


    float B[9] = {
	(a.x - r.origin.x), -Ec.x, r.direction.x,
	(a.y - r.origin.y), -Ec.y, r.direction.y,
	(a.z - r.origin.z), -Ec.z, r.direction.z };    

    float A[9] = {
	-Eb.x, -Ec.x, r.direction.x,
	-Eb.y, -Ec.y, r.direction.y,
	-Eb.z, -Ec.z, r.direction.z };    

    float dt = findDeterminant(T);
    float dc = findDeterminant(C);
    float db = findDeterminant(B);
    float da = findDeterminant(A);


    float t = dt/da;
    float beta = db/da;
    float y = dc/da;
    t_small = t;
    return (beta > 0 && y > 0 && beta + y < 1);
}


int pixelOn(float pixel_x, float pixel_y, const vector<Face>& f)
{

    Ray current(lightPos, Vector3(pixel_x, pixel_y, 1000) - lightPos);
    current.direction.normalize();
    float min = -1.0;
    int min_i = -1;
    for(int i = 0; i < f.size(); i++)
    {
	//see if ray hit this face
	
	float t_small;
	if(hitPolygon(current, f[i], t_small))
	{
	    //compute light for this face
	    if(min == -1)
	    {
		min = t_small;
		min_i = i;

	    }
	    else if(t_small < min)
	    {
		min = t_small;
		min_i = i;


	    }
	}
    }
    return min_i;
}



void GL_render()
{
    //glClearColor( 0.2f, 0.2f, 0.5f, 0.0f );

    glClear(GL_COLOR_BUFFER_BIT);
    clearZBuffer();
    //clearFrameBuffer();


    vector<Face> tFaces;
    vector<Vertex> tVertices;
    for(int i = 0; i < all3DPoints.size(); i++)
    {
	tVertices.push_back(Vertex(transformPoint(all3DPoints[i].position)));
    }
    
    for(int i = 0 ; i < faces.size(); i++)
    {
	float r = ambientLight.r;
	float b = ambientLight.b;
	float g = ambientLight.g;
	//compute lighting for this triangle
	//get normal we computed for this triangle
	Vector3 vector1 = tVertices[faces[i].index1].position - tVertices[faces[i].index3].position;
	Vector3 vector2 = tVertices[faces[i].index2].position - tVertices[faces[i].index3].position;
	Vector3 cProd = vector1.crossProduct(vector2);	
	cProd.normalize();
	//faces[i].normal = cProd;
	Face tmp(&tVertices[faces[i].index1],
		 &tVertices[faces[i].index2],
		 &tVertices[faces[i].index3]);
	tmp.normal = cProd;
	tFaces.push_back(tmp);

    }
    //recalculate normals
    for(int i = 0; i < tVertices.size();i++)
    {
	//for each vertex get the avg of faces around it
	int numTris = 0;
	for(int j = 0; j < tFaces.size(); j++)
	{

	    if(faces[j].index1 == i)
	    {
		numTris++;
		tVertices[i].normal += tFaces[j].normal;
	    }
	    else if(faces[j].index2 == i)
	    {
		numTris++;
		tVertices[i].normal += tFaces[j].normal;
	    }
	    else if(faces[j].index3 == i)
	    {
		numTris++;
		tVertices[i].normal += tFaces[j].normal;
	    }
	}
	tVertices[i].normal /= numTris;
	tVertices[i].normal.normalize();
	//cerr << tVertices[i].normal.x << " " << tVertices[i].normal.y << " " << tVertices[i].normal.z << endl;
    }
    //shoot a ray from the light source to every pixel on the screen
    for(int i = 0; i < 800; i++)
    {
	for(int j = 0; j < 800; j++)
	{
	    int which_sphere = pixelOn(i, 800 - j, tFaces);
            if(which_sphere == -1)
	    {

		//LETS DO PHONG LOL
		if(!flat)
		{
		Vector3 pixel = Vector3(i,j,1000);
		float r = ambientLight.r;
		float b = ambientLight.b;
		float g = ambientLight.g;
		Vector3 lightVector =pixel - lightPos;
		lightVector.normalize();
	    
		//compute lighting for this triangle
		//get normal we computed for this triangle
		Vector3 cProd(0,0,-1.0f);
		//Vector3 pixelNormal = getInterpolatedNormal(f,pixel);
		float d = (cProd.dot(lightVector));
		d = abs(d);

		Vector3 reflectionVector;
		reflectionVector = reflectedRay(lightVector, cProd);
		reflectionVector.normalize();
		//find dot between 400,400,-400 and point
		Vector3 viewerVector = pixel - Vector3(400,400,0);
		viewerVector.normalize();
		float d2 = viewerVector.dot(reflectionVector);
		//cerr << d2 << endl;
		d2 = pow(d2,50);		
		r = (r * d * diffuseLight.r) + (specularCoefficient * d2) - 0.05;
		if(r > 1)
		    r = 1;

		b = (b * d * diffuseLight.b) + (specularCoefficient * d2) - 0.05;
		if(b > 1)
		    b = 1;

		g = (g * d * diffuseLight.g) + (specularCoefficient * d2) - 0.05;
		if(g > 1)
		    g= 1;
		renderPixel(i, 800 - j, r,g,b);
		}
		else
		{
		float r = ambientLight.r;
		float b = ambientLight.b;
		float g = ambientLight.g;
		renderPixel(i, 800 - j, r,g,b);
		}
	    }
	    else
	    {
		if(!flat)
		{
		//LETS DO PHONG LOL
		Vector3 pixel = Vector3(i,j,1000);
		float r = ambientLight.r;
		float b = ambientLight.b;
		float g = ambientLight.g;
		Vector3 lightVector =pixel - lightPos;
		lightVector.normalize();
	    
		//compute lighting for this triangle
		//get normal we computed for this triangle
		Vector3 cProd(0,0,-1.0f);
		//Vector3 pixelNormal = getInterpolatedNormal(f,pixel);
		float d = (cProd.dot(lightVector));
		d = abs(d);
		r = (r * d)/5;
		if(r > 1)
		    r = 1;

		b = (b * d)/5;
		if(b > 1)
		    b = 1;

		g = (g * d)/5;
		if(g > 1)
		    g= 1;
		renderPixel(i, 800 - j, r,g,b);
		}
		else
		{
		float r = ambientLight.r;
		float b = ambientLight.b;
		float g = ambientLight.g;
		renderPixel(i, 800 - j, r/5,g/5,b/5);
		}
	    }
	}

    }
    for(int i = 0; i < tFaces.size(); i++)

    {
	float r,g,b;
	project3Dto2D(tFaces[i],
		      r,g,b);	
    }
    glutSwapBuffers();
}

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



