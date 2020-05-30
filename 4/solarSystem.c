/* TODO
 * - glutWireTorus per le orbite dei pianeti
 * -
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

void initPlanets(void);
void init(void);
void drawPlanets(void);
void display(void);
int  main(int, char**);

#define PLANETS_MAX	9

typedef struct _planet_t {
	GLdouble radius,
			 r,
			 g,
			 b,
			 distance;
    int     speed,
            currentAngle;
} Planet;

static Planet planets[PLANETS_MAX];
static int angle = 0;

void rotatePlanetAngle(int val) {
    angle = (angle + 5) % 360;
    glutPostRedisplay();
    glutTimerFunc(1000/60, rotatePlanetAngle, angle);
}

void drawPlanets() {
	GLUquadric *quad;
	quad = gluNewQuadric();

	for(int i = 0; i < PLANETS_MAX; i++) {
		glPushMatrix();
		// color
		glColor3f(planets[i].r, planets[i].g, planets[i].b);
        
        // angle
        glRotatef((GLfloat) angle, 0.0, 1.0, 0.0);   
        
        // position
		glTranslatef(planets[i].distance, 0.0, 0.0);
        
		// sphere
		glutWireSphere(planets[i].radius, 20, 20);

		glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glColor3f(0.8, 0.8, 0.8);
        glutWireTorus(.001, planets[i].distance, 100.0, 100.0);
        glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// push initial modelview matrix
	glPushMatrix();
	
	// draw elements in the scene
	drawPlanets();

	// pop initial modelview matrix
	glPopMatrix();

	// flush graphics objects immediately
	glFlush();

	//glutSwapBuffers();
}

void initPlanets() {
	// Sun
	planets[0].r		= 1.0;
	planets[0].g		= 1.0;
	planets[0].b		= 0.0;
	planets[0].radius	= 5.0;
	planets[0].distance	= 0.0;

	// Mercury
	planets[1].r		= 0.5;
	planets[1].g		= 0.3;
	planets[1].b		= 0.0;
	planets[1].radius	= 1.0;
	planets[1].distance	= 7.0;

	// Venus
	planets[2].r		= 1.0;
	planets[2].g		= 0.5;
	planets[2].b		= 0.0;
	planets[2].radius	= 1.5;
	planets[2].distance	= 11.0;

	// Earth
	planets[3].r		= 0.0;
	planets[3].g		= 0.0;
	planets[3].b		= 1.0;
	planets[3].radius	= 2.0;
	planets[3].distance	= 16.0;

	// Mars
	planets[4].r		= 1.0;
	planets[4].g		= 0.2;
	planets[4].b		= 0.0;
	planets[4].radius	= 1.2;
	planets[4].distance	= 21.0;

	// Jupiter
	planets[5].r		= 1.0;
	planets[5].g		= 0.5;
	planets[5].b		= 0.0;
	planets[5].radius	= 3.5;
	planets[5].distance	= 28.0;

	// Saturn
	planets[6].r		= 1.0;
	planets[6].g		= 0.7;
	planets[6].b		= 0.0;
	planets[6].radius	= 3.0;
	planets[6].distance	= 37.0;

	// Uranus
	planets[7].r		= 0.7;
	planets[7].g		= 0.7;
	planets[7].b		= 1.0;
	planets[7].radius	= 2.5;
	planets[7].distance	= 45.5;

	// Neptune
	planets[8].r		= 0.3;
	planets[8].g		= 0.3;
	planets[8].b		= 1.0;
	planets[8].radius	= 2.3;
	planets[8].distance	= 53.6;
}

void init() {
	GLenum glErr;

	// initalize planet values
	initPlanets();

	// clearing color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	// initialize viewing values
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// set viewing frustum
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 120.0);

	if((glErr=glGetError()) != 0) {
        printf("[E](%d)\n", glErr);
        exit(2);
    }

	// initialize model view transforms
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0.0, 70, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutTimerFunc(1000/60, rotatePlanetAngle, angle);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(500, 300);
	glutCreateWindow("Solar System");

	GLenum err = glewInit();
	if(err != GLEW_OK) {
		fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
		exit(1);
	}

	init();
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}