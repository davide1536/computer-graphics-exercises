#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define ELEMENTS    9               // 8 planets + 1 star

#define SLICES      20
#define STACKS      20

/* DELTA
 * (represents the element's speed)
 */
#define DELTA       (1.0/500.0)

typedef struct planet_t {
    GLfloat radius;
    GLfloat color[3];
    GLfloat distance[3];
    // GLfloat speed;
} Planet;


// di seguito sono lasciati commentati i valori non in scala
#define SUN         5.0//2.0    // 1.7
#define MERCURY     1.0//0.07   // 0.2
#define VENUS       1.5//0.094  // 0.4
#define EARTH       2.0//0.1    // 0.6
#define MARS        1.2//0.06   // 0.5
#define JUPITER     3.5//1.1    // 0.8
#define SATURN      3.0//0.94   // 0.7
#define URANUS      2.5//0.4    // 0.6
#define NEPTUNE     2.3//0.388  // 0.5

GLfloat elementsSize[ELEMENTS] = {
    SUN,
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE
};

GLfloat elementsColor[ELEMENTS][3] = {
    {1.0, 1.0, 0.0},
    {0.5, 0.3, 0.0},
    {1.0, 0.5, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.2, 0.0},
    {1.0, 0.5, 0.0},
    {1.0, 0.7, 0.0},
    {0.7, 0.7, 1.0},
    {0.3, 0.3, 1.0}
};

GLfloat elementsTranslate[ELEMENTS] = {
    0,
    7,
    11,
    16,
    21,
    28,
    37,
    45.5,
    53.6
    /* -15.0,
    -13.0,
    -12.0,
    -11.0,
    -10.0,
    -7.5,
    -5.5,
    -3.5,
    -2.0 */
};

// current angle
static float currAlpha = 0;

// planet array
static Planet planets[ELEMENTS];

/* void initPlanets() {
    // Sun
    planets[0].color    = {1.0, 1.0, 0.0};
    planets[0].distance = {0.0, 0.0, -15.0};
    planets[0].radius   = 2.0;
    // Mercury
    planets[1].color    = {1.0, 1.0, 0.0};
    planets[1].distance = {0.5, 0.3, 0.0};
    planets[1].radius   = 0.07;
    // Venus
    planets[2].color    = {1.0, 0.5, 0.0};
    planets[2].distance = {0.0, 0.0, -12.0};
    planets[2].radius   = 0.94;
    // Earth
    planets[3].color    = {0.0, 0.0, 1.0};
    planets[3].distance = {0.0, 0.0, -11.0};
    planets[3].radius   = 0.1;
    // Mars
    planets[4].color    = {1.0, 0.2, 0.0};
    planets[4].distance = {0.0, 0.0, -10.0};
    planets[4].radius   = 0.06;
    // Jupiter
    planets[5].color    = {1.0, 0.5, 0.0};
    planets[5].distance = {0.0, 0.0, -7.5};
    planets[5].radius   = 1.1;
    // Saturn
    planets[6].color    = {1.0, 0.7, 0.0};
    planets[6].distance = {0.0, 0.0, -5.5};
    planets[6].radius   = 0.94;
    // Uranus
    planets[7].color    = {0.7, 0.7, 1.0};
    planets[7].distance = {0.0, 0.0, -3.5};
    planets[7].radius   = 0.4;
    // Neptune
    planets[8].color    = {0.3, 0.3, 1.0};
    planets[8].distance = {0.0, 0.0, -2.0};
    planets[8].radius   = 0.388;
    
}
 */

/* drawElements: draw the sun and other planets 
 * in the scene.
 */
void drawElements() {
    GLUquadric *quad;
    GLfloat currPos[2] = { 0.0, 0.0 };
    quad = gluNewQuadric();
    
    // draw elements: initial position
    for (int i = 0; i < ELEMENTS; i++) {
        glPushMatrix();

        glColor3f(elementsColor[i][0], elementsColor[i][1], elementsColor[i][2]);
        
        glTranslatef(elementsTranslate[i], 0.0, 0.0);
        
        /* currPos[0] = 15*cos(currAlpha * 2 * M_PI);
        currPos[1] = 5*sin(currAlpha * 2 * M_PI); */

        // draw a sphere
        gluSphere(quad, elementsSize[i], SLICES, STACKS);

        glPopMatrix();
    }
}

/* uploadPosition: updates currAlpha adding a DELTA
 * to update the element's position.
 */
void uploadPosition(int value) {
    currAlpha += DELTA;
    
    if (currAlpha > 1.0) 
        currAlpha = 0.0;
    
    glutPostRedisplay();

    /* glutTimerFunc calls uploadPosition() every 16ms
     * it calls this function only once, so we need to
     * specify another call at the end of the function
     */
    glutTimerFunc(1000/60, uploadPosition, 0);
}

// display routine
void display(void) {
    
    // push initial state on the stack
    glPushMatrix();

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElements();
   
    glFlush();
    // redraw scene
    //glutPostRedisplay();
}

void init (void) {
    GLenum glErr;

    // select clearing color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 200.0);
    //(-5.0, 5.0, -5.0, 5.0, 1, 50.0);

    // ... it does not hurt to check that everything went OK
    if((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 50, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookAt(10,1,-10,0,0,-10,0,1,0);
    //gluLookAt(3,12,0,0,0,-10,0,1,0);

    //glutTimerFunc(1000/60,uploadPosition, 0);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            // ESC
            exit(0);
            break;
        case '1':
            // Key 1
            // update display
            glutPostRedisplay();
            break;
        default:
            // do nothing
            break;
    }
}

// Window size and mode
int main(int argc, char** argv) {

    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(200, 200);
    glutCreateWindow ("OpenGL Window");

    // keyboard handling function
    glutKeyboardFunc(keyInput);

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
