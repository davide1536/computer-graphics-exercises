/*
 * OpenGL: push/pop example
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define DELTA   (1.0/500.0)

GLfloat startEndPoints[2][3] =
{{0.0, 0.0, 0.0}, {0.0, 0.0, -4.0}};

GLfloat currPos[2];
static float currAlpha = 0;

void uploadPosition(int value) {
    glutTimerFunc(1000/60,uploadPosition, 0);
    currAlpha += DELTA;
    if (currAlpha > 1.0) currAlpha = 0.0;
            glutPostRedisplay();
}
// display routine
void display(void)
{
    
    // push initial state on the stack
    glPushMatrix();

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // place objects in the scene
    //glTranslatef(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0,-15.0);

    // draw wireframe sphere
    GLUquadric *quad;
    quad = gluNewQuadric();                                                             
    gluSphere(quad,2.0,100,20);
    
    glPopMatrix();
    glPushMatrix();

    for (int i = 0; i<2; i++) {
        glPushMatrix();
        currPos[0] = 15*cos(currAlpha * 2 * M_PI);
        currPos[1] = 5*sin(currAlpha * 2 * M_PI);
        printf("pos = %f \n", currPos[0]);
        glTranslatef(0.0+currPos[0], 0.0,  -12.0+currPos[1]);
        glColor3f(0.3, 0.3, 1.0);                          
        gluSphere(quad,0.388,100,20);
        glPopMatrix();
    }

    // glPopMatrix();
    // glPushMatrix();


    // glColor3f(1.0, 0.2, 0.3);  
    // glTranslatef(0.0, 0.0,-20.0);                                                     
    // gluSphere(quad,0.5,100,20);

    // glPopMatrix();
    // glPushMatrix();

    // glColor3f(1.0, 0.2, 0.3);  
    // glTranslatef(10, 0.0,-6.0);                                                     
    // gluSphere(quad,0.5,100,20);
    // glutWireSphere(1.0, 20.0, 20.0);
    // flush graphics objects immediately
    // pop initial state on the stack
   
    glPopMatrix();
    glFlush();
    // redraw scene
    //glutPostRedisplay();
}

void init (void)
{
    GLenum glErr;

    // select clearing color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-2.0, 2.0, -2.0, 2.0, 1, 50.0);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3,12,0,0,0,-10,0,1,0);
    glutTimerFunc(1000/60,uploadPosition, 0);

}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key) {
        case 27:
            // ESC
            exit(0);
            break;
        case '1':
            // Key 1
            // update display
            currAlpha += DELTA;
            if (currAlpha > 1.0) currAlpha = 0.0;
            glutPostRedisplay();
            break;
        default:
            // do nothing
            break;
    }
}

// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
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

