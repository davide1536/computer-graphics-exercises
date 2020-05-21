/*
* Draw a cube ... triangles
*/
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

// number of faces
#define NFACES          4
// number of vertices per face
#define NVERTICES       24

/* Uncomment only ONE of the following macros */
#define MODE_TRIANGLES
//#define MODE_VBO
//#define MODE_DRAWARRAYS

GLfloat vertexArray[NFACES * NVERTICES * 3] = {
    // first face
    -0.5,-0.5,0.5,
    0.5,-0.5,0.5,
    0.5,-0.2,0.5,

    -0.5,-0.5,0.5,
    -0.5,-0.2,0.5,
    0.5,-0.2,0.5,

    -0.5,0.1,0.5,
    0.5,0.1,0.5,
    0.5,0.5,0.5,

    -0.5,0.1,0.5,
    -0.5,0.5,0.5,
    0.5,0.5,0.5,

    -0.5,-0.2,0.5,
    -0.5,0.1,0.5,
    (-0.5+0.2),-0.2,0.5,

    -0.5+0.2,-0.2,0.5,
    -0.5+0.2,0.1,0.5,
    -0.5,0.1,0.5,

    0.5,-0.2,0.5,
    0.5,0.1,0.5,
    (0.5-0.2),-0.2,0.5,

    0.5-0.2,-0.2,0.5,
    0.5-0.2,0.1,0.5,
    0.5,0.1,0.5,

    // second face
    -0.5,-0.5,-0.5,
    -0.5,-0.5,0.5,
    -0.5,-0.2,0.5,

    -0.5,-0.5,-0.5,
    -0.5,-0.2,-0.5,
    -0.5,-0.2,0.5, 

    -0.5,0.1,0.5,
    -0.5,0.1,-0.5,
    -0.5,0.5,-0.5,

    -0.5,0.1,0.5,
    -0.5,0.5,0.5,
    -0.5,0.5,-0.5,

    -0.5,-0.2,-0.5,
    -0.5,0.1,-0.5,
    -0.5,-0.2,(-0.5+0.2),

    -0.5,-0.2,-0.5+0.2,
    -0.5,0.1,-0.5+0.2,
    -0.5,0.1,-0.5,

    -0.5,-0.2,0.5,
    -0.5,0.1,0.5,
    -0.5,-0.2,(0.5-0.2),

    -0.5,-0.2,0.5-0.2,
    -0.5,0.1,0.5-0.2,
    -0.5,0.1,0.5,
    
    // third face
    0.5,-0.5,-0.5,
    0.5,-0.5,0.5,
    0.5,-0.2,0.5,

    0.5,-0.5,-0.5,
    0.5,-0.2,-0.5,
    0.5,-0.2,0.5, 

    0.5,0.1,0.5,
    0.5,0.1,-0.5,
    0.5,0.5,-0.5,

    0.5,0.1,0.5,
    0.5,0.5,0.5,
    0.5,0.5,-0.5,

    0.5,-0.2,-0.5,
    0.5,0.1,-0.5,
    0.5,-0.2,(-0.5+0.2),

    0.5,-0.2,-0.5+0.2,
    0.5,0.1,-0.5+0.2,
    0.5,0.1,-0.5,

    0.5,-0.2,0.5,
    0.5,0.1,0.5,
    0.5,-0.2,(0.5-0.2),

    0.5,-0.2,0.5-0.2,
    0.5,0.1,0.5-0.2,
    0.5,0.1,0.5,
    
    // fourth face
    0.5,-0.5,-0.5,
    -0.5,-0.5,-0.5,
    -0.5,-0.2,-0.5,

    0.5,-0.5,-0.5,
    0.5,-0.2,-0.5,
    -0.5,-0.2,-0.5,

    0.5,0.1,-0.5,
    -0.5,0.1,-0.5,
    -0.5,0.5,-0.5,

    0.5,0.1,-0.5,
    0.5,0.5,-0.5,
    -0.5,0.5,-0.5,

    0.5,-0.2,-0.5,
    0.5,0.1,-0.5,
    (0.5-0.2),-0.2,-0.5,

    0.5-0.2,-0.2,-0.5,
    0.5-0.2,0.1,-0.5,
    0.5,0.1,-0.5,

    -0.5,-0.2,-0.5,
    -0.5,0.1,-0.5,
    (-0.5+0.2),-0.2,-0.5,

    -0.5+0.2,-0.2,-0.5,
    -0.5+0.2,0.1,-0.5,
    -0.5,0.1,-0.5,
};

GLfloat colorArray[NFACES*NVERTICES*3] = {
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, 0.5, 0.0
};

unsigned int buffers[2];

GLint vertexIndices[NFACES*NVERTICES];

// display function
void display(void)
{
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // store modelview settings
    glPushMatrix();

    // place the cube in the scene
    glTranslatef(0.0, 0.0, -1.5);
    glTranslatef(0.0, -.8, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);

    #ifdef MODE_TRIANGLES
    /* NFACE*NVERTICES glVertex calls */
        glBegin(GL_TRIANGLES);       
        // first faace
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(-0.5,-0.5,0.5);
            glVertex3f(0.5,-0.5,0.5);
            glVertex3f(0.5,-0.2,0.5);

            glVertex3f(-0.5,-0.5,0.5);
            glVertex3f(-0.5,-0.2,0.5);
            glVertex3f(0.5,-0.2,0.5);

            glVertex3f(-0.5,0.1,0.5);
            glVertex3f(0.5,0.1,0.5);
            glVertex3f(0.5,0.5,0.5);

            glVertex3f(-0.5,0.1,0.5);
            glVertex3f(-0.5,0.5,0.5);
            glVertex3f(0.5,0.5,0.5);

            glVertex3f(-0.5,-0.2,0.5);
            glVertex3f(-0.5,0.1,0.5);
            glVertex3f((-0.5+0.2),-0.2,0.5);

            glVertex3f(-0.5+0.2,-0.2,0.5);
            glVertex3f(-0.5+0.2,0.1,0.5);
            glVertex3f(-0.5,0.1,0.5);

            glVertex3f(0.5,-0.2,0.5);
            glVertex3f(0.5,0.1,0.5);
            glVertex3f((0.5-0.2),-0.2,0.5);

            glVertex3f(0.5-0.2,-0.2,0.5);
            glVertex3f(0.5-0.2,0.1,0.5);
            glVertex3f(0.5,0.1,0.5);
        
        // second face
            glColor3f(0.0, 1.0, 0.0);

            glVertex3f(-0.5,-0.5,-0.5);
            glVertex3f(-0.5,-0.5,0.5);
            glVertex3f(-0.5,-0.2,0.5);

            glVertex3f(-0.5,-0.5,-0.5);
            glVertex3f(-0.5,-0.2,-0.5);
            glVertex3f(-0.5,-0.2,0.5); 

            glVertex3f(-0.5,0.1,0.5);
            glVertex3f(-0.5,0.1,-0.5);
            glVertex3f(-0.5,0.5,-0.5);

            glVertex3f(-0.5,0.1,0.5);
            glVertex3f(-0.5,0.5,0.5);
            glVertex3f(-0.5,0.5,-0.5);

            glVertex3f(-0.5,-0.2,-0.5);
            glVertex3f(-0.5,0.1,-0.5);
            glVertex3f(-0.5,-0.2,(-0.5+0.2));

            glVertex3f(-0.5,-0.2,-0.5+0.2);
            glVertex3f(-0.5,0.1,-0.5+0.2);
            glVertex3f(-0.5,0.1,-0.5);

            glVertex3f(-0.5,-0.2,0.5);
            glVertex3f(-0.5,0.1,0.5);
            glVertex3f(-0.5,-0.2,(0.5-0.2));

            glVertex3f(-0.5,-0.2,0.5-0.2);
            glVertex3f(-0.5,0.1,0.5-0.2);
            glVertex3f(-0.5,0.1,0.5);
        
        // third face
            glColor3f(0.0, 0.0, 1.0);

            glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(0.5,-0.5,0.5);
            glVertex3f(0.5,-0.2,0.5);

            glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(0.5,-0.2,-0.5);
            glVertex3f(0.5,-0.2,0.5); 

            glVertex3f(0.5,0.1,0.5);
            glVertex3f(0.5,0.1,-0.5);
            glVertex3f(0.5,0.5,-0.5);

            glVertex3f(0.5,0.1,0.5);
            glVertex3f(0.5,0.5,0.5);
            glVertex3f(0.5,0.5,-0.5);

            glVertex3f(0.5,-0.2,-0.5);
            glVertex3f(0.5,0.1,-0.5);
            glVertex3f(0.5,-0.2,(-0.5+0.2));

            glVertex3f(0.5,-0.2,-0.5+0.2);
            glVertex3f(0.5,0.1,-0.5+0.2);
            glVertex3f(0.5,0.1,-0.5);

            glVertex3f(0.5,-0.2,0.5);
            glVertex3f(0.5,0.1,0.5);
            glVertex3f(0.5,-0.2,(0.5-0.2));

            glVertex3f(0.5,-0.2,0.5-0.2);
            glVertex3f(0.5,0.1,0.5-0.2);
            glVertex3f(0.5,0.1,0.5);
        
        // fourth face
            glColor3f(0.5, 0.5, 0.0);
            
            glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(-0.5,-0.5,-0.5);
            glVertex3f(-0.5,-0.2,-0.5);

            glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(0.5,-0.2,-0.5);
            glVertex3f(-0.5,-0.2,-0.5);

            glVertex3f(0.5,0.1,-0.5);
            glVertex3f(-0.5,0.1,-0.5);
            glVertex3f(-0.5,0.5,-0.5);

            glVertex3f(0.5,0.1,-0.5);
            glVertex3f(0.5,0.5,-0.5);
            glVertex3f(-0.5,0.5,-0.5);

            glVertex3f(0.5,-0.2,-0.5);
            glVertex3f(0.5,0.1,-0.5);
            glVertex3f((0.5-0.2),-0.2,-0.5);

            glVertex3f(0.5-0.2,-0.2,-0.5);
            glVertex3f(0.5-0.2,0.1,-0.5);
            glVertex3f(0.5,0.1,-0.5);

            glVertex3f(-0.5,-0.2,-0.5);
            glVertex3f(-0.5,0.1,-0.5);
            glVertex3f((-0.5+0.2),-0.2,-0.5);

            glVertex3f(-0.5+0.2,-0.2,-0.5);
            glVertex3f(-0.5+0.2,0.1,-0.5);
            glVertex3f(-0.5,0.1,-0.5);
        glEnd();
    #elif defined(MODE_DRAWARRAYS) || defined(MODE_VBO)
    /* Draw vertex data from array */
        for(GLshort indFace=0; indFace<NFACES; indFace++) {
            glDrawArrays(GL_TRIANGLES, indFace*NVERTICES, NVERTICES);
        };
    #endif

    // restore model view settings
    glPopMatrix();

    // flush graphics objects immediately
    glFinish();
}

void init (void)
{
    // select clearing color
    glClearColor (0.0, 0.0, 0.0, 0.0);

    #if defined(MODE_DRAWARRAYS) || defined(MODE_VBO)
    /* Enable Vertex/Color arrays client-side feature 
     * for DrawArray and DrawArray+VBO modes.
     */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);      
    #endif

    #ifdef MODE_VBO
    /* Index buffer generation */
        glGenBuffers(2, buffers);
    /* buffer[0]: vertexArray indexes */
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray) + sizeof(colorArray), NULL, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexArray), vertexArray);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexArray), sizeof(colorArray), colorArray);
    /* buffer[1]: colorArray indexes */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

        for(int currInd=1; currInd < NFACES*NVERTICES; currInd++) 
            vertexIndices[currInd]=currInd;
        vertexIndices[0] = 3;
        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(vertexArray)));
    #endif

    #ifdef MODE_DRAWARRAYS
    /* Simply specify the initial arrays as vertexPointer/colorPointer */
        glVertexPointer(3, GL_FLOAT, 0, vertexArray);
        glColorPointer(3, GL_FLOAT, 0, colorArray);
    #endif

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-0.2, 0.2, -0.3, 0.1, 0.1, 5.0);

    // ... it does not hurt to check that everything went OK
    if (glGetError() != 0) {
        exit(-1);
    }

    // Turn on wireframe mode (only for debugging purposes)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // IMPORTANT: initialize the depth buffer
    // otherwise things are displayed erratically!
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
}

// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("OpenGL Window");

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // Call initialization routinesx
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
