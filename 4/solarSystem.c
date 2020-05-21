/*
 * OpenGL: push/pop example
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define ELEMENTS    9       // 8 planets + 1 star

#define SLICES      100
#define STACKS      20

// di seguito sono lasciati commentati i valori non in scala
#define SUN         2.0    // 1.7
#define MERCURY     0.07   // 0.2
#define VENUS       0.094  // 0.4
#define EARTH       0.1    // 0.6
#define MARS        0.6    // 0.5
#define JUPITER     1.1    // 0.8
#define SATURN      0.94   // 0.7
#define URANUS      0.4    // 0.6
#define NEPTUNE     0.388  // 0.5

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

GLfloat elementsTranslate[ELEMENTS][3] = {
    {0.0, 0.0, -16.0},
    {0.0, 0.0, -13.0},
    {0.0, 0.0, -12.0},
    {0.0, 0.0, -10.5},
    {0.0, 0.0, -9.0},
    {0.0, 0.0, -7.5},
    {0.0, 0.0, -5.5},
    {0.0, 0.0, -3.5},
    {0.0, 0.0, -2.0}
};

// display routine
void display(void) {

    // push initial state on the stack
    glPushMatrix();

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw wireframe sphere
    GLUquadric *quad;
    quad = gluNewQuadric();

    for (int i = 0; i < ELEMENTS; i++) {  
        glPushMatrix();
        
        // specify color
        glColor3f(elementsColor[i][0], elementsColor[i][1], elementsColor[i][2]);
        
        // specify translate coordinates to place the element in the scene
        glTranslatef(elementsTranslate[i][0], elementsTranslate[i][1], elementsTranslate[i][2]);
        
        // draw a sphere
        gluSphere(quad, elementsSize[i], SLICES, STACKS);
        
        glPopMatrix();
    }

    glFlush();
    // redraw scene
    //glutPostRedisplay();
}

void init (void) {
    GLenum glErr;

    // select clearing color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // VBO for colorArray
    // enable color array
    glEnableClientState(GL_COLOR_ARRAY);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 20.0);

    // ... it does not hurt to check that everything went OK
    if((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10,1,-10,0,0,-10,0,1,0);

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

    glutInitWindowSize(800, 800);
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
