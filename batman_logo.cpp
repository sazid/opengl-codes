#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

#define mp std::make_pair

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void drawBatmanLogo();

int main(int argc, char **argv) {
    // Initialize glut
    glutInit(&argc, argv);

    // Set display mode
    // GLUT_DOUBLE - enable double buffering
    // GLUT_RGBA - RGBA color for display
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Set window size
    glutInitWindowSize(500, 500);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("Assignment 2 | 17-33330-1");

    // Initialize OpenGL
    initOpenGL();

    // Set the display function callback, which will be called
    // over and over again, from glut's main loop
    glutDisplayFunc(display);

    // Callback for when glut will remain idle
    glutIdleFunc(display);

    // Callback for when the window state is changed (like resize)
    glutReshapeFunc(reshape);

    // Start the main loop
    glutMainLoop();

    return 0;
}

void display() {
    // Use the preset color (using glClearColor) to redraw the color buffer
    // Call this to clear the current buffer and start anew
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the logo
    glColor3ub(0, 0, 0);
    drawBatmanLogo();

    // After all the drawing is done, swap the two buffers (double buffer)
    // MUST CALL this
    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
    // Viewport defines the part of the window where OpenGL is going to draw
    // x, y - starts at the lower left corner of the window
    // w, h - width and height of the viewport starting from x and y
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    // set the color
    glClearColor(0.95, 0.95, 0.95, 1.0);
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	// loads identity matrix
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
    glLoadIdentity();
    gluPerspective(100, 500.0 / 500.0, 1, 30);
	// set the viewing camera
	// first 3 values indicate eye(x,y,z) - camera
	// second 3 indicates center(x,y,z) - the point where eye is looking
	// next 3 indicates UP vector(x,y,z) - look up or down from eye point
    gluLookAt(0, 1, 9, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// change default point size of (-1 to 1) to (-5 to 5)
    glPointSize(5);
}

void drawWithMirror(std::vector<std::pair<GLdouble, GLdouble> > v) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < (int)v.size(); ++i) {
		glVertex2d(v[i].first, v[i].second);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < (int)v.size(); ++i) {
		glVertex2d(-v[i].first, v[i].second);
	}
	glEnd();
}

void drawBatmanLogo() {
	// inner side of head
	drawWithMirror({
		mp(0, 1.4),
		mp(.1, 1.37),
		mp(.2,1.35),
		mp(.2,0),
		mp(0,0)
	});
	
	// ear
	drawWithMirror({
		mp(.2,1.35),
		mp(.4,2),
		mp(.5,1),
		mp(.5,-1),
		mp(.2,0)
	});
	
	// tail
	drawWithMirror({
		mp(0,0),
		mp(.6,0),
		mp(.5,-1),
		mp(0,-2)
	});

	// body partial
	drawWithMirror({
		mp(.3,.9),
		mp(.8,.9),
		mp(1.1,-.6),
		mp(.5,-1)
	});

	// wing parts
	drawWithMirror({
		mp(0,0),
		mp(.85,-.75),
		mp(.4,-1.15)
	});

	drawWithMirror({
		mp(.8,.9),
		mp(1.2,1),
		mp(2.35,-0.1)
	});

	drawWithMirror({
		mp(.8,.9),
		mp(1.1,-.6),
		mp(2.35,-.1)
	});

	drawWithMirror({
		mp(1.2,1),
		mp(1.4,1.1),
		mp(3.9,0),
		mp(2.35,-.1)
	});

	drawWithMirror({
		mp(1.4,1.1),
		mp(1.6,1.3),
		mp(4.15,.5),
		mp(3.9,0)
	});

	drawWithMirror({
		mp(1.6,1.3),
		mp(1.75,1.6),
		mp(4.4,.85),
		mp(4.15,.5)
	});

	drawWithMirror({
		mp(1.75,1.6),
		mp(1.85,1.9),
		mp(5,1.3),
		mp(4.4,.85)
	});

	drawWithMirror({
		mp(1.85,1.9),
		mp(1.9,2.2),
		mp(7,2.2),
		mp(5,1.3)
	});
}

