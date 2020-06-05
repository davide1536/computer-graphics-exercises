#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

void rotatePlanetAngle(int);
void loopPlanets(void);
void initPlanets(void);
void init(void);
void drawPlanets(void);
void display(void);
void writeText(void);
void writeStrokeString(void *font, char *string);
int  main(int, char**);

/* Uncomment to enable lighting. */
//#define LIGHTING

/* Uncomment to enable planet orbit animations. */
#define ANIMATION
// #define LIGHTING
#define SLICES      20
#define STACKS      20

/* Total number of planets in the scene. */
#define PLANETS_MAX	9
const float DEG2RAD = 3.14159/180.0;

typedef struct _planet_material_t {
	float	matAmbient[4],
			matDiffuse[4],
			matSpecular[4],
			shine[1];
} PlanetMaterial;

/* struct Planet: represents planets info, such as:
 * - radius
 * - distance from the sun (sun.distance = 0)
 * - color (r, g, b)
 * - orbit speed
 * - x, y (current step of the orbit)
 * - 
 */
typedef struct _planet_t {
	GLdouble        radius;
	GLdouble        distance;
	GLdouble        x,
					y;
	GLdouble        xMaxOrbit,
					yMaxOrbit;
	GLdouble		r,
			 		g,
			 		b;
	PlanetMaterial 	material;
	int             speed,
					currentAngle;
} Planet;

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
	{0.1, 0.1},			/* Sun */
	{7.0, 5.0},			/* Mercury */
	{11.0, 10.0},		/* Venus */
	{16.0, 14.0},		/* Earth */
	{24.0, 20.0},		/* Mars */
	{28.0, 24.0},		/* Jupiter */
	{37.0, 28.0},		/* Saturn */
	{45.5, 30.0},		/* Uranus */
	{53.6, 48.0},		/* Neptune */
};

/* Materials (lighting). */
PlanetMaterial planetMaterials[PLANETS_MAX] = {
	{{0.5,0.5,1.0},{1.0,1.0,0.0,1.0},{0,0,0,1.0},{20.0}},

	{{0.6,0.3,0.0,1.0},{0.4,0.3,0.5,1.0},{0,0,0,1.0},{20.6}},

	{{0.74,0.59,0.074,1.0},{0.35,0.20,0.22,1.0},{0.0,0.0,0.0,1.0},{20.0}},

	{{0.1,0.18,0.17,0.8},{0.39,0.74,0.69,0.8},{0.29,0.30,0.30,1.0},{20.0}},

	{{0.19,0.07,0.02,1.0},{0.70,0.27,0.082,1.0},{0.25,0.13,0.08,1.0},{12.0}},

	{{0.25,0.14,0.06,1.0},{0.4,0.23,0.10,1.0},{0.77,0.45,0.20,1.0},{76.0}},

	{{0.25,0.20,0.20,0.92},{1.0,0.82,0.82,0.92},{0.29,0.29,0.29,1.0},{11.0}},

	{{0.0,0.1,0.06,1.0},{0.0,0.5,0.5,1.0},{0.5,0.5,0.5,1.0},{32.0}},
	
	{{0.10,0.05,0.11,1.0},{0.42,0.47,0.54,1.0},{0.33,0.33,0.52,1.0},{9.84}}
};

static Planet planets[PLANETS_MAX];
static int angle = 0;

void writeStrokeString(void *font, char *string) {

   char *c;
   for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

void writeText() {
	char* PLANETS_NAME[PLANETS_MAX] = {"Sole","Merc.", "Vene.", "Terra", "Marte", "Giove", "Saturno", "Urano", "Nettuno"};
	for (int i = 0; i<PLANETS_MAX; i++) {
	float TextPosition = planets[i].x-planets[i].radius/2;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	if (i!=0) {
	glRotatef((GLfloat) angle, 0.0, 1.0, 0.0); 
	if (i%2 == 0) 
		glTranslatef(TextPosition, planets[i].y+5, 0.0);
	else 
		glTranslatef(TextPosition, planets[i].y-10, 0.0);
	glRotatef((GLfloat) -angle, 0.0, 1.0, 0.0);
	}
	else {
		glTranslatef(TextPosition, planets[i].y+5, 0.0);
	}
    glScalef(0.02, 0.02, 0.0);
    writeStrokeString(GLUT_STROKE_ROMAN, PLANETS_NAME[i]);
    glPopMatrix();
	}
}

void rotatePlanetAngle(int val) {
	angle = (angle + 1) % 360;
	glutPostRedisplay();
	glutTimerFunc(1000/60, rotatePlanetAngle, angle);
}

/* loopPlanets: update all planet's coordinates
 * in order to perform an elliptical orbit
 * around the sun.
 */
/* void loopPlanets() {
	float degInRad;
	for(int i = 1; i < PLANETS_MAX; i++) {
		// Draw orbital trails
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
	
} */

void drawPlanets() {
	GLUquadric *quad;
	quad = gluNewQuadric();
	

	for(int i = 0; i < PLANETS_MAX; i++) {
	
		glPushMatrix();
		/* Colors */
		glColor3f(planets[i].r, planets[i].g, planets[i].b);
		
		/* Angle */
		glRotatef((GLfloat) angle, 0.0, 1.0, 0.0);   
		
		/* Position */
		glTranslatef(planets[i].x, planets[i].y, 0.0);

		/* Assign a material to each planet */
			// if (i==0) {
			// 	GLfloat brightness[] = {1.0f,1.0f,0.0f,1.0f};
			// 	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,brightness);
			// 	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   planets[i].material.matAmbient);
			// }
			//else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   planets[i].material.matAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   planets[i].material.matDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  planets[i].material.matSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, planets[i].material.shine);
			//}
			/* glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, planetMaterials[i].matAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, planetMaterials[i].matDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, planetMaterials[i].matSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,planetMaterials[i].shine); */
		
		

		/* Draw a sphere */
		//glutWireSphere(planets[i].radius, 20, 20);
		 gluSphere(quad, planets[i].radius, SLICES, STACKS);
		glPopMatrix();

		// draw orbit trail
		/* glBegin(GL_POINTS);
			glColor3f(0.8, 0.8, 0.8);
			for(int j = 0; j < 360; j++) {
				float degInRad = j*DEG2RAD;
				glVertex3f(cos(degInRad)*planets[i].xMaxOrbit, sin(degInRad)*planets[i].yMaxOrbit, 0.0);
			}
		glEnd(); */

		// No, that won't work.
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		//glColor3f(0.8, 0.8, 0.8);

		//set default materials to draw orbits' lines 
		float mat_ambient []={0.2, 0.2, 0.2, 1.0};
    	float mat_diffuse []={ 0.8, 0.8, 0.8, 1.0 };
    	float mat_specular[] ={ 0.0f, 0.0f, 0.0f, 1.0f };
    	float shine []= {0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
		//glColor3f(0, 0, 0); 

		glutWireTorus(.001, planets[i].xMaxOrbit, 100.0, 100.0);
		glPopMatrix();
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GLfloat lightPos[4] = {0};
	GLfloat lightPos[4] = {0.01,0.1,0,0};

	/* Push initial modelview matrix */
	glPushMatrix();
	
	/* Initialize light position */
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	writeText();
	/* Draw elements in the scene */
	glEnable(GL_LIGHT0);

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
		/* Lighting materials */
		planets[i].material 	= planetMaterials[i];
	}
}

void init() {
	GLenum glErr;

	// initalize planet values
	initPlanets();

	
		// Light init
		float globAmb[] = {0.2, 0.2, 0.2, 1.0};
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
	glClearColor(1.0, 1.0, 1.0, 1.0);

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

	#ifdef LIGHTING
		glShadeModel(GL_SMOOTH);
	#endif

	#ifdef ANIMATION
		glutTimerFunc(1000/60, rotatePlanetAngle, angle);
	#endif
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