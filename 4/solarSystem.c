#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

void rotatePlanetAngle(int);
void loopPlanets(void);
void initPlanets(void);
void initLights(void);
void init(void);
void drawPlanets(void);
void display(void);
int  main(int, char**);

/* Total number of planets in the scene. */
#define PLANETS_MAX	9
const float DEG2RAD = 3.14159/180.0;

/* struct Planet: represents planets info, such as:
 * - radius
 * - distance from the sun (sun.distance = 0)
 * - color (r, g, b)
 * - orbit speed
 * - x, y (current step of the orbit)
 * - 
 */
typedef struct _planet_t {
	GLdouble radius;
	GLdouble distance;
	GLdouble r, 
			 g, 
			 b;
	GLdouble x,
			 y;
	GLdouble xMaxOrbit,
			 yMaxOrbit;
	int      speed,
			 currentAngle;
} Planet;

=======
/* Initial coordinates of the planets (x, 0.0, 0.0). */
GLdouble planetCoordinates[PLANETS_MAX] = {
	0.0,                /* Sun */
	7.0,                /* Mercury */
	11.0,               /* Venus */
	16.0,               /* Earth */
	21.0,               /* Mars */
	28.0,               /* Jupiter */
	37.0,				/* Saturn */
	45.5,				/* Uranus */
	53.6				/* Neptune */
};

/* Colors of the planets. */
GLdouble planetColors[PLANETS_MAX][3] = {
	{1.0, 1.0, 0.0},    /* Sun */
	{0.5, 0.3, 0.0},    /* Mercury */
	{1.0, 0.5, 0.0},    /* Venus */
	{0.0, 0.0, 1.0},    /* Earth */
	{1.0, 0.2, 0.0},    /* Mars */
	{1.0, 0.5, 0.0},    /* Jupiter */
	{1.0, 0.7, 0.0},    /* Saturn */
	{0.7, 0.7, 1.0},    /* Uranus */
	{0.3, 0.3, 1.0}     /* Neptune */
};

/* Radius of every planet. */
GLdouble planetRadiuses[PLANETS_MAX] = {
	5.0,				/* Sun */
	1.0,				/* Mercury */
	1.5,				/* Venus */
	2.0,				/* Earth */
	1.2,				/* Mars */
	3.5,				/* Jupiter */
	3.0,				/* Saturn */
	2.5,				/* Uranus */
	2.3					/* Neptune */	
};

/* Orbit coordinates. 
* TODO redundancy: x coord already referenced by planet's inital x parameter
*/
GLdouble planetMaxOrbit[PLANETS_MAX][2] = {
	{0.0, 0.0},			/* Sun */
	{7.0, 5.0},			/* Mercury */
	{11.0, 10.0},		/* Venus */
	{16.0, 14.0},		/* Earth */
	{24.0, 20.0},		/* Mars */
	{28.0, 24.0},		/* Jupiter */
	{37.0, 28.0},		/* Saturn */
	{45.5, 30.0},		/* Uranus */
	{53.6, 48.0},		/* Neptune */
};
>>>>>>> a00a503601f838b4f8933985b99216e8683a0d2d

static Planet planets[PLANETS_MAX];
planetMaterial planetsMaterials[PLANETS_MAX-1];
static int angle = 0;

void rotatePlanetAngle(int val) {
	angle = (angle + 5) % 360;
	glutPostRedisplay();
	glutTimerFunc(1000/60, rotatePlanetAngle, angle);
}

/* loopPlanets: update all planet's coordinates
 * in order to perform an elliptical orbit
 * around the sun.
 */
void loopPlanets() {
	float degInRad;
	for(int i = 1; i < PLANETS_MAX; i++) {
		/* Draw orbital trails */
		glBegin(GL_POINTS);
			glColor3f(0.8, 0.8, 0.8);
			for(int j = 0; j < 360; j++) {
				degInRad = j*DEG2RAD;
				glVertex3f(cos(degInRad)*planets[3].xMaxOrbit, sin(degInRad)*planets[3].yMaxOrbit, 0.0);
			}
		glEnd();

		planets[i].currentAngle = planets[i].currentAngle > 359 ? 0 : planets[i].currentAngle + 1;

		planets[i].x = cos(planets[i].currentAngle*DEG2RAD)*planets[i].xMaxOrbit;
		planets[i].y = sin(planets[i].currentAngle*DEG2RAD)*planets[i].xMaxOrbit;
		glPushMatrix();
		glTranslatef(planets[i].x, planets[i].y,0.0f);
		glRotatef(angle,0.0f,1.0f,0.0f);
		glutSolidSphere(); //????
		glPopMatrix();
	}
	
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
		glTranslatef(planets[i].x, planets[i].y, 0.0);
		
		// sphere
		glutWireSphere(planets[i].radius, 20, 20);

		glPopMatrix();

		// draw orbit trail
		glBegin(GL_POINTS);
			glColor3f(0.8, 0.8, 0.8);
			for(int j = 0; j < 360; j++) {
				float degInRad = j*DEG2RAD;
				glVertex3f(cos(degInRad)*planets[i].xMaxOrbit, sin(degInRad)*planets[i].yMaxOrbit, 0.0);
			}
		glEnd();
		/* glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glColor3f(0.8, 0.8, 0.8);
		glutWireTorus(.001, planets[i].xMaxOrbit, 100.0, 100.0);
		glPopMatrix(); */
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Push initial modelview matrix */
	glPushMatrix();
	
	/* Draw elements in the scene */
	drawPlanets();

	/* Pop initial modelview matrix */
	glPopMatrix();

	/* Flush graphics objects immediately */
	glFlush();

	/* Double buffering */
	glutSwapBuffers();
}

void initPlanets() {
	for(int i = 0; i < PLANETS_MAX; i++) {
		/* Color */
		planets[i].r			= planetColors[i][0];
		planets[i].g			= planetColors[i][1];
		planets[i].b			= planetColors[i][2];
		/* Coordinates */
		planets[i].x			= planetCoordinates[i];
		planets[i].y 			= 0.0;
		/* Radius  */
		planets[i].radius		= planetRadiuses[i];
		/* Max orbit coordinates */
		planets[i].xMaxOrbit 	= planetMaxOrbit[i][0];
		planets[i].yMaxOrbit	= planetMaxOrbit[i][1];
		/* Current angle */
		planets[i].currentAngle	= 0;
	}
/* 	// Sun
	planets[0].r		= 1.0;
	planets[0].g		= 1.0;
	planets[0].b		= 0.0;
	planets[0].radius	= 5.0;
	planets[0].distance	= 0.0;
	planets[0].x        = 0.0;
	planets[0].y        = 0.0;

	// Mercury
	planets[1].r		= 0.5;
	planets[1].g		= 0.3;
	planets[1].b		= 0.0;
	planets[1].radius	= 1.0;
	planets[1].distance	= 7.0;
	planets[1].x        = 7.0;
	planets[1].y        = 0.0;

	// Venus
	planets[2].r		= 1.0;
	planets[2].g		= 0.5;
	planets[2].b		= 0.0;
	planets[2].radius	= 1.5;
	planets[2].distance	= 11.0;
	planets[2].x        = 11.0;
	planets[2].y        = 0.0;

	// Earth
	planets[3].r		= 0.0;
	planets[3].g		= 0.0;
	planets[3].b		= 1.0;
	planets[3].radius	= 2.0;
	planets[3].distance	= 16.0;
	planets[3].x        = 16.0;
	planets[3].y        = 0.0;

	// Mars
	planets[4].r		= 1.0;
	planets[4].g		= 0.2;
	planets[4].b		= 0.0;
	planets[4].radius	= 1.2;
	planets[4].distance	= 21.0;
	planets[4].x        = 21.0;
	planets[4].y        = 0.0;

	// Jupiter
	planets[5].r		= 1.0;
	planets[5].g		= 0.5;
	planets[5].b		= 0.0;
	planets[5].radius	= 3.5;
	planets[5].distance	= 28.0;
	planets[5].x        = 28.0;
	planets[5].y        = 0.0;

	// Saturn
	planets[6].r		= 1.0;
	planets[6].g		= 0.7;
	planets[6].b		= 0.0;
	planets[6].radius	= 3.0;
	planets[6].distance	= 37.0;
	planets[6].x        = 37.0;
	planets[6].y        = 0.0;

	// Uranus
	planets[7].r		= 0.7;
	planets[7].g		= 0.7;
	planets[7].b		= 1.0;
	planets[7].radius	= 2.5;
	planets[7].distance	= 45.5;
	planets[7].x        = 45.5;
	planets[7].y        = 0.0;

	// Neptune
	planets[8].r		= 0.3;
	planets[8].g		= 0.3;
	planets[8].b		= 1.0;
	planets[8].radius	= 2.3;
	planets[8].distance	= 53.6;
	planets[8].x        = 53.6;
	planets[8].y        = 0.0;
	 */
}
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
	gluLookAt(0.0, 70.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//glutTimerFunc(1000/60, rotatePlanetAngle, angle);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

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