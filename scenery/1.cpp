#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void drawRoad();
void drawCar(GLdouble xx, GLdouble yy, GLdouble scale=1.0);
void drawTireWholes(GLdouble x, GLdouble y, GLdouble z, GLdouble angle);
void drawMountains();
void drawSun();
void drawWindmill(GLdouble x, GLdouble y, GLdouble scale);

namespace sazid {
    // Draw the string s at the specified position - x, y
    void drawString(GLdouble x, GLdouble y, std::string const& s, void* font);

    // Draw a circle from the given center - cx, cy with radius r
    // steps indicate how smooth the circle will be, greater - smoother
    void drawCircle(GLdouble cx, GLdouble cy, GLfloat r, GLint steps);

    // Draw a rectangle from the given x, y position with width and height - w, h
    void drawRectangle(GLdouble x, GLdouble y, GLdouble w, GLdouble h);
}

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
    glutCreateWindow("Assignment 1 | 17-33330-1");

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

	// To operate on Model-View matrix
	glMatrixMode(GL_MODELVIEW);
	// Reset the Model-View matrix
	glLoadIdentity();

    drawSun();
    drawMountains();
	drawWindmill(0.8, 0.26, 0.8);
	drawWindmill(0.5, 0.3, 1);
    drawRoad();

    glColor3ub(10,100,100);
    drawCar(0, 0.1, 0.6);

    glColor3ub(100,50,50);
    drawCar(0.5, -0.2, 0.6);

    // After all the drawing is done, swap the two buffers (double buffer)
    // MUST CALL this
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

void initOpenGL() {
    // set the color
    glClearColor(0.95, 0.95, 0.95, 1.0);
}

void sazid::drawString(GLdouble x, GLdouble y, std::string const& s, void* font) {
    // font - GLUT_BITMAP_HELVETICA_18 or anything available
    glRasterPos2d(x, y);
    for (std::string::size_type i = 0; i < s.size(); ++i) {
        glutBitmapCharacter(font, s[i]);
    }
}

void sazid::drawCircle(GLdouble cx, GLdouble cy, GLfloat r, GLint steps) {
    glBegin(GL_TRIANGLE_FAN);
        // Center of the circle
        glVertex2f(cx, cy);
        GLfloat angle;
        for (GLint i = 0; i <= steps; ++i) {
            angle = i * 2.0f * PI / steps;
            glVertex2f(std::cos(angle) * r + cx, std::sin(angle) * r + cy);
        }
    glEnd();
}

void sazid::drawRectangle(GLdouble x, GLdouble y, GLdouble w, GLdouble h) {
    glBegin(GL_QUADS);

        glVertex2d(x, y);
        glVertex2d(x, y + h);
        glVertex2d(x - w, y + h);
        glVertex2d(x - w, y);

    glEnd();
}

void drawRoad() {
    glBegin(GL_LINES);

        glColor3ub(0, 0, 0);

        glVertex2d(-1, 0.1);
        glVertex2d(1, 0.1);

        glVertex2d(-1, -0.5);
        glVertex2d(1, -0.5);

    glEnd();

    glColor3ub(150, 150, 150);
    sazid::drawRectangle(0.9, -0.25, 0.4, 0.03);
    sazid::drawRectangle(0.2, -0.25, 0.4, 0.03);
    sazid::drawRectangle(-0.4, -0.25, 0.4, 0.03);
    sazid::drawRectangle(-0.9, -0.25, 0.4, 0.03);
}

GLdouble x = -1.5;
GLdouble addFactor = 0.01;
GLdouble tireAddFactor = -5;
GLdouble tireAngle = 0.0;

void drawCar(GLdouble xx, GLdouble yy, GLdouble scale) {
	glPushMatrix();
	glTranslated(xx + x + addFactor, yy, 0.0);
	glScaled(scale, scale, 0.0);

    //glColor3ub(10,100,100);
    sazid::drawRectangle(0.4, -0.2, 0.8, 0.4);

    glBegin(GL_QUADS);

        // front bumper
        glVertex2d(0.55, -0.2);
        glVertex2d(0.55, -0.05);
        glVertex2d(0.4, 0.2);
        glVertex2d(0.4, -0.2);

        // rear spoiler
        glVertex2d(-0.4, -0.2);
        glVertex2d(-0.4, 0.2);
        glVertex2d(-0.48, 0.22);
        glVertex2d(-0.48, -0.2);

        // top hood
        glVertex2d(0.2, 0.2);
        glVertex2d(0.15, 0.23);
        glVertex2d(-0.15, 0.23);
        glVertex2d(-0.2, 0.2);

        glColor3ub(50,50,50);

        // rear window
        glVertex2d(-0.01, -0.02);
        glVertex2d(-0.01, 0.15);
        glVertex2d(-0.35, 0.15);
        glVertex2d(-0.35, -0.02);

        // front window
        glVertex2d(0.4, -0.02);
        glVertex2d(0.3, 0.15);
        glVertex2d(0.03, 0.15);
        glVertex2d(0.03, -0.02);

    glEnd();

    // front wheel
    glColor3ub(0, 0, 0);
    sazid::drawCircle(0.35, -0.2, 0.125, 100);
    glColor3ub(50,50,50);
    sazid::drawCircle(0.35, -0.2, 0.1, 100);
    glColor3ub(0,0,0);
	drawTireWholes(0.35, -0.2, 0.0, tireAngle);

    // rear wheel
    glColor3ub(0,0,0);
    sazid::drawCircle(-0.25, -0.2, 0.125, 100);
    glColor3ub(50,50,50);
    sazid::drawCircle(-0.25, -0.2, 0.1, 100);
    glColor3ub(0,0,0);
	drawTireWholes(-0.25, -0.2, 0.0, tireAngle);

    x += addFactor;
	tireAngle += tireAddFactor;
    if (x >= 1.5 or x <= -1.5) {
        addFactor = (-1) * addFactor;
		tireAddFactor = (-1) * tireAddFactor;
    }

	glPopMatrix();
}

void drawMountains() {
    glBegin(GL_TRIANGLES);

        glColor3ub(105, 105, 105);
        glVertex2d(1.4, 0.1);
        glVertex2d(0.8, 0.8);
        glVertex2d(0.2, 0.1);

        glColor3ub(100, 100, 100);
        glVertex2d(0.8, 0.1);
        glVertex2d(0.4, 0.4);
        glVertex2d(0.0, 0.1);

        glColor3ub(110, 110, 110);
        glVertex2d(0.3, 0.1);
        glVertex2d(-0.3, 0.65);
        glVertex2d(-0.9, 0.1);

        glColor3ub(105, 105, 105);
        glVertex2d(0.5, 0.1);
        glVertex2d(0, 0.55);
        glVertex2d(-0.5, 0.1);

        glColor3ub(100, 100, 100);
        glVertex2d(-0.3, 0.1);
        glVertex2d(-0.8, 0.75);
        glVertex2d(-1.4, 0.1);

    glEnd();
}

GLdouble sunRadius = 0.0;
GLdouble glowFactor = 0.0001;
void drawSun() {
    glColor3ub(255, 120, 0);
    sazid::drawCircle(0.7, 0.8 , 0.18 + sunRadius, 100);
    glColor3ub(250, 90, 0);
    sazid::drawCircle(0.7, 0.8 , 0.15 + sunRadius, 100);
    glColor3ub(248, 50, 0);
    sazid::drawCircle(0.7, 0.8 , 0.12 + sunRadius, 100);
    glColor3ub(245, 10, 0);
    sazid::drawCircle(0.7, 0.8 , 0.1 + sunRadius, 100);

    sunRadius += glowFactor;
    if (sunRadius >= 0.05 or sunRadius <= 0.0) {
        glowFactor = (-1) * glowFactor;
    }
}

void drawTireWholes(GLdouble x, GLdouble y, GLdouble z, GLdouble angle) {
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(angle, 0.0, 0.0, 1.0);

	sazid::drawCircle(0.0, 0.055, 0.015, 5);
	sazid::drawCircle(0.0, -0.055, 0.015, 5);
	sazid::drawCircle(0.055, 0.0, 0.015, 5);
	sazid::drawCircle(-0.055, 0.0, 0.015, 5);

	angle += 1.0;
	glPopMatrix();
}

void drawFan(GLdouble x, GLdouble y, GLdouble angle) {
	glPushMatrix();
		glTranslated(x, y, 0.0);
		glRotated(angle, 0.0, 0.0, 1.0);

		glColor3f(0.2f, 0.2f, 0.2f);
		sazid::drawCircle(0.0, 0.0, 0.03, 4);

		glBegin(GL_TRIANGLES);
			glVertex2f(-0.03f, -0.18f);
			glVertex2f( 0.03f, -0.18f);
			glVertex2f( 0.0f,  0.0f);
		glEnd();
	glPopMatrix();
}

GLdouble fanAngle = 0.0;
void drawWindmill(GLdouble x, GLdouble y, GLdouble scale) {
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glScaled(scale, scale, 0.0);

	glBegin(GL_TRIANGLES);
		glColor3f(0.1f, 0.1f, 0.1f); // Grey
		glVertex2f(-0.05f, -0.2f);
		glVertex2f( 0.05f, -0.2f);
		glVertex2f( 0.0f,  0.2f);
	glEnd();


	drawFan(0.0, 0.19, 120.0 + fanAngle);
	drawFan(0.0, 0.19, 240.0 + fanAngle);
	drawFan(0.0, 0.19, 360.0 + fanAngle);
	fanAngle += 1;

	glPopMatrix();
}

