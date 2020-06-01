/* TODO
 * - glutWireTorus per le orbite dei pianeti
 * -
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

void initPlanets(void);
void initLights(void);
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

typedef struct _planetMaterial_t {
	float	mat_ambient[4],
			mat_diffuse[4],
			mat_specular[4],
			shine[1];
} planetMaterial;

static Planet planets[PLANETS_MAX];
planetMaterial planetsMaterials[PLANETS_MAX-1];
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
        
		//assign a material to each planet
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, planetsMaterials[i].mat_ambient);
   		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, planetsMaterials[i].mat_ambient);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, planetsMaterials[i].mat_specular);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,planetsMaterials[i].shine);

		// sphere
		glutWireSphere(planets[i].radius, 20, 20);

		glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//light position is equal to sun position 
	GLfloat lightPos[4] = {0};
	// push initial modelview matrix
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
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
void initLights() {
	// Sun
	planetsMaterials[PLANETS_MAX-1] = {	
	 
	// {{0.5,,0.0,1.0},{1.0,1.0,0.0,1.0},{0,0,0,1.0},{20.0}},
	{{0.6,0.3,0.0,1.0},{0.4,0.3,0.5,1.0},{0,0,0,1.0},{20.6}},

	{{ 0.74,0.59,0.074,1.0},{0.35,0.20,0.22,1.0},{0.0,0.0,0.0,1.0},{20.0}},

	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}},

	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}},

	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}},

	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}},

	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}},
	
	{{0.5,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{0,0,0,1.0},{20.0}}

	};
	// //mercury
	// planetsMaterials[1].mat_ambient[]	= {1.0};
	// planetsMaterials[1].mat_diffuse[]	= {1.0};
	// planetsMaterials[1].mat_specular[]	= {1.0};
	// planetsMaterials[1].shine[]			= {1.0};
	// //venus
	// planetsMaterials[2].mat_ambient		= {1.0};
	// planetsMaterials[2].mat_diffuse		= {1.0};
	// planetsMaterials[2].mat_specular	= {1.0};
	// planetsMaterials[2].shine			= {1.0};
	// //earth
	// planetsMaterials[3].mat_ambient		= {1.0};
	// planetsMaterials[3].mat_diffuse		= {1.0};
	// planetsMaterials[3].mat_specular	= {1.0};
	// planetsMaterials[3].shine			= {1.0};
	// //mars
	// planetsMaterials[4].mat_ambient		= {1.0};
	// planetsMaterials[4].mat_diffuse		= {1.0};
	// planetsMaterials[4].mat_specular	= {1.0};
	// planetsMaterials[4].shine			= {1.0};
	// //jupiter
	// planetsMaterials[5].mat_ambient		= {1.0};
	// planetsMaterials[5].mat_diffuse		= {1.0};
	// planetsMaterials[5].mat_specular	= {1.0};
	// planetsMaterials[5].shine			= {1.0};
	// //saturn
	// planetsMaterials[6].mat_ambient		= {1.0};
	// planetsMaterials[6].mat_diffuse		= {1.0};
	// planetsMaterials[6].mat_specular	= {1.0};
	// planetsMaterials[6].shine			= {1.0};
	// //uranus
	// planetsMaterials[7].mat_ambient		= {1.0};
	// planetsMaterials[7].mat_diffuse		= {1.0};
	// planetsMaterials[7].mat_specular	= {1.0};
	// planetsMaterials[7].shine			= {1.0};
	// //neptune
	// planetsMaterials[8].mat_ambient		= {1.0};
	// planetsMaterials[8].mat_diffuse		= {1.0};
	// planetsMaterials[8].mat_specular	= {1.0};
	// planetsMaterials[8].shine			= {1.0};
}

void init() {
	GLenum glErr;

	// initalize planet values
	initPlanets();

	initLights();

	//define light
	float globAmb[] = {0.0, 0.0, 0.0, 1.0};

    // Light vectors.
    float lightAmb[] = {0.2, 0.2,0.2, 1.0};
    float lightDif[] = {1.0, 1.0, 1.0, 1.0};
    float lightSpec[] = {1.0, 1.0, 1.0, 1.0};
	
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    // Global ambient light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    // Enable local viewpoint.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

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
    gluLookAt(0.0, 50, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);

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