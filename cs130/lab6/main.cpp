// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <cmath>
#include <list>
#include <GL/glut.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float VIEW_LEFT = 0.0;
const float VIEW_RIGHT = WINDOW_WIDTH;
const float VIEW_BOTTOM = 0.0;
const float VIEW_TOP = WINDOW_HEIGHT;
const float VIEW_NEAR = -400;
const float VIEW_FAR = 400;

// Retrieve random float
float randFloat()
{
	return rand() / static_cast<float>(RAND_MAX);
}
float randFloat(float min, float max)
{
	return randFloat() * (max - min) + min;
}

// A simple wrapper for store 3D vectors
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() : x(0.0), y(0.0), z(0.0)
	{}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vector3(const Vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{}

	Vector3 operator+(const Vector3 & rhs) const
	{ return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator-(const Vector3 & rhs) const
	{ return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator*(float rhs) const
	{ return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator/(float rhs) const
	{ return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3 operator+=(const Vector3 & rhs)
	{ x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3 operator-=(const Vector3 & rhs)
	{ x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3 operator*=(float rhs)
	{ x *= rhs; y *= rhs; z *= rhs; return *this; }
	Vector3 operator/=(float rhs)
	{ x /= rhs; y /= rhs; z /= rhs; return *this; }

	float magnitude() const
	{ return sqrt(x * x + y * y + z * z); }
	void normalize()
	{ *this /= magnitude(); }
	Vector3 normalized() const
	{ return *this / magnitude(); }
	float dot(const Vector3 & rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vector3 cross(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);
	}
};

// A simple wrapper to store colors
struct Color3d
{
	float r;
	float g;
	float b;
	float a;

	Color3d()
		: r(0.0), g(0.0), b(0.0), a(1.0)
	{}
	Color3d(float r, float g, float b, float a = 1.0)
		: r(r), g(g), b(b), a(a)
	{}
};

struct Particle
{
	// Important attributes of a particle which are respectively
	// position, velocity, acceleration, color, and lifetime timer.
	Vector3 pos;
	Vector3 vel;
	Vector3 acc;
	Color3d col;
	float timer;
    bool expired;
	Particle()
	    : pos(), vel(), col(), acc(), timer(0.0), expired(false)
	{}
	Particle(const Vector3 & pos, const Vector3 & vel, const Vector3 & acc, const Color3d & col, float timer)
	    : pos(pos), vel(vel), acc(acc), col(col), timer(timer), expired(false)
	{}

	/* Complete this function */
	bool isExpired() const
	{
		return expired;
	}

	/* Complete this function */
	void update(float elapsed)
	{
	    //make sure we pass in the time + elapsed into timer
	    pos.x += vel.x * elapsed;
	    pos.y += vel.y * elapsed;
	    vel.x = vel.x + acc.x * elapsed;
	    vel.y = vel.y + acc.y * elapsed;
	    col.r+=elapsed/3;
	    col.g+=elapsed/3;
	    col.b+=elapsed/3;
	    timer -= elapsed;
	    expired = (timer < 0);
	    //keep it from giong below 0
	    if(pos.y < 1)
	    {
		pos.y = 1;
		vel.y = -vel.y;
	    }
	}

	void render()
	{
		glColor4f(col.r, col.g, col.b, col.a);
		glVertex3f(pos.x, pos.y, pos.z);
	}
};

struct ParticleSystem
{
	// List of all unexpired particles
	std::list<Particle> particles;
	
	ParticleSystem(const Vector3 & spawnPoint)
		: particles()
	{
		init(spawnPoint);
	}

	/* Complete this function */
	void init(const Vector3 & spawnPoint)
	{
	    //create particles
	    //make a fuckton
	    for(int i = 0 ; i < 20; i++)
	    {
	    particles.push_back(Particle(spawnPoint, 
					 Vector3(randFloat(-50,50),randFloat(0,200),0),
					 Vector3(randFloat(-50,50),-400,0),
					 Color3d(0,0,0,1),
					 4.0f));
	    }
	}

	/* Returns true if there are no particles present */
	bool isEmpty() const
	{
		return particles.size() <= 0;
	}

	void update(float elapsed)
	{
		std::list<Particle>::iterator it;

		// Update all particles
		for (it = particles.begin(); it != particles.end(); ++it)
		{
			it->update(elapsed);
		}
		
		// Remove any expired particles from the list
		for (it = particles.begin(); it != particles.end();)
		{
			if (it->isExpired())
				it = particles.erase(it);
			else
				++it;
		}
	}

	/* Renders all particles as single points */
	void render()
	{
	    glPointSize(5);
		glBegin(GL_POINTS);
		std::list<Particle>::iterator it;
		for (it = particles.begin(); it != particles.end(); ++it)
		{
			it->render();
		}
		glEnd();
	}
};

std::list<ParticleSystem> psystems;

// Number of seconds between frame updates
const float FRAME_PERIOD = 0.001;

// Used to approximate the time between updates
int currentTime = 0;
int previousTime = 0;

// A time accumulator for determining when to render the next frame
float elapsed = 0.0;

void GLrender();
void GLupdate();

void buttonFunction(int button, int state, int x, int y)
{
    if(state == GLUT_UP)
    {
	psystems.push_back(ParticleSystem(Vector3(x,800-y,0)));
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab 9 - <Insert Name Here>");
	glutDisplayFunc(GLrender);
	glutIdleFunc(GLupdate);
	glutMouseFunc(buttonFunction);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glOrtho(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, VIEW_NEAR, VIEW_FAR);
}

int main(int argc, char** argv)
{
	GLInit(&argc, argv);

	glutMainLoop();
	return 0;
}

void GLupdate()
{
	// Update time elapsed
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int diffTime = currentTime - previousTime;
	previousTime = currentTime;

	elapsed += (diffTime / 1000.0);

	// See if the accumulated elapsed time is enough render the next frame.	
	if (elapsed > FRAME_PERIOD)
	{


		std::list<ParticleSystem>::iterator it;

		// Update all existed particle systems
		for (it = psystems.begin(); it != psystems.end(); ++it)
		{
			it->update(elapsed);
		}

		// Clean up all empty (inactive) particle sytems
		for (it = psystems.begin(); it != psystems.end();)
		{
			if (it->isEmpty())
				it = psystems.erase(it);
			else
				++it;
		}

		glutPostRedisplay();
		elapsed = 0;
	}
}

void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Render all particle systems	
  std::list<ParticleSystem>::iterator it;
	for (it = psystems.begin(); it != psystems.end(); ++it)
	{
		it->render();
	}
	glFlush();	
	glutSwapBuffers();
}

