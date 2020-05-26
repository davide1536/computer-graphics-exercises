/*
 * This is a simple program that computes FPS
 * by means of a circular buffer
 */
#include <GL/glut.h>
//#include <numeric>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>

// Y axis scale
#define Y_SCALE 0.6
// X axis points
#define X_POINTS 10

// plot positioning
#define X_OFFSET -0.03
#define Y_OFFSET 0.3
#define Z_OFFSET -1

// Buffer used to compute frame rate
float frames[X_POINTS];

int firstInd = 0;
int nEls = 0;
int nLines,counter = 0;

void handler(int signal) {
	exit(0);
}

// function to get the number of elapsed ticks
uint32_t getTick()
{
	struct timespec ts;
	unsigned theTick = 0U;
	clock_gettime( CLOCK_REALTIME, &ts );
	theTick  = ts.tv_nsec / 1000000;
	theTick += ts.tv_sec * 1000;
	return theTick;
}

// accumulate buffer and update window title
int computeAndShowFrameRate(void)
{
	static float lastTime = 0.0f;
	static unsigned int frameCount = 0;
	char windowTitle[100];
	float sumFPS;

	float currentTime = (float)getTick() * 0.001f; //da ms a sec
	// Initialize lastTime to the current time
	if (lastTime == 0) {
		lastTime = currentTime;
	}

	// increase frame count
	frameCount++;
	if (currentTime - lastTime > 1.0f) {
		
		// insert the current fps in the circular buffer
		frames[counter] = ((float)frameCount) / (currentTime - lastTime);

		// update variable lastTime
		lastTime = currentTime;
		frameCount = 0;

		// sum elements in circular buffer
		//sumFPS = sumCircularBuffer(); //calcolo per un solo valore
		snprintf(windowTitle, 100, "FPS = %6.2f", frames[counter]);
		// update window title
		nLines += 10000;
		counter++;
		glutSetWindowTitle(windowTitle);
	}
}

// perform a "stress test" to gather data for the final plot 
void drawLines() {
	for (int currLineInd = 0; currLineInd<nLines; currLineInd++) {
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f((float)rand()/RAND_MAX,(float)rand()/RAND_MAX, -1);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f((float)rand()/RAND_MAX,(float)rand()/RAND_MAX, -1);
		glEnd();
	}
	glutPostRedisplay();
}

// draw simple plot using data obtained from the last stress test
void drawSimplePlot() {
	int i;
	// draw x-axis points
	for (i = 1; i <= X_POINTS; i++) {
		glBegin(GL_POINTS);
			glColor3f(1,1, 1);
			glVertex3f( ((float)i/X_POINTS)+X_OFFSET, Y_OFFSET, Z_OFFSET );
		glEnd();
	}

	// draw lines representing refreshes per seconds
	glBegin(GL_LINES);
		for (i = 1; i <= X_POINTS; i++) {
			if (i == X_POINTS || i == 1)
				glVertex3f(((float)i/X_POINTS)+X_OFFSET, ((float) Y_SCALE*frames[i-1]/60)+Y_OFFSET, Z_OFFSET);
			for(int j = 0; j < 2; j++)
				glVertex3f(((float)i/X_POINTS)+X_OFFSET, ((float) Y_SCALE*frames[i-1]/60)+Y_OFFSET, Z_OFFSET);
		}
	glEnd();
}

// display function
void display(void)
{
	// get current frame rate
	computeAndShowFrameRate();
	// clear buffer
	//glClearColor ((float)rand()/RAND_MAX,(float)rand()/RAND_MAX,(float)rand()/RAND_MAX, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(counter < X_POINTS)  // this will allow the curve to end with the last X axis point (specified by X_POINT)
		drawLines();
	else
		drawSimplePlot();

	glFinish();
	glutSwapBuffers();
}

// initialization function
void init (void)
{
	// Use current time as seed for random generator
	srand(time(0));

	nLines = 5000;
	// select clearing color
	glClearColor (0.0, 0.0, 0.0, 0.0);

	// Orthographic projection
	glOrtho(0.0f, 1.0, 0.0f , 1.0, 0.0f, 1.0);
}
// Window size and mode
int main(int argc, char** argv)
{
	signal(SIGINT, handler);

	// pass potential input arguments to glutInit
	glutInit(&argc, argv);

	// set display mode
	// GLUT_SINGLE = single buffer window
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize (400, 400);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("My first window");

	// Call initialization routinesx
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
