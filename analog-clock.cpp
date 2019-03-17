#pragma region
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void Timer(GLint value);
void drawClock();

void drawHourHand();
void drawMinuteHand();
void drawSecondHand();

GLint refreshTimeMillis = 1000;
// elasped time in seconds
GLint elaspedTime = 0;

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
//    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    // Set window size
    glutInitWindowSize(500, 500);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("Final Assignment 1 | 17-33330-1");

    // Initialize OpenGL
    initOpenGL();

    // Set the display function callback, which will be called
    // over and over again, from glut's main loop
    glutDisplayFunc(display);

    // Callback for when glut will remain idle
    // glutIdleFunc(display);

    // Callback for when the window state is changed (like resize)
    glutReshapeFunc(reshape);

    // Callback for controlling timer (FPS)
    glutTimerFunc(0, Timer, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}

void Timer(GLint value) {
    glutPostRedisplay();
    ++elaspedTime;
    glutTimerFunc(refreshTimeMillis, Timer, 0);
}

void display() {
    // Use the preset color (using glClearColor) to redraw the color buffer
    // Call this to clear the current buffer and start anew
    glClear(GL_COLOR_BUFFER_BIT);

	// To operate on Model-View matrix
	glMatrixMode(GL_MODELVIEW);
	// Reset the Model-View matrix
	glLoadIdentity();

	drawClock();

    // After all the drawing is done, swap the two buffers (double buffer)
    // MUST CALL this
    glutSwapBuffers();
}
#pragma endregion

void drawFrame() {
    glColor3ub(54, 54, 54);
    sazid::drawCircle(0.0, 0.0, .5, 100);

    glColor3ub(255, 255, 255);
    sazid::drawCircle(0.0, 0.0, .435, 100);
}

void drawHourTicks() {
    glColor3ub(54, 54, 54);
    GLdouble angle = 30.0;
    for (int i = 0; i < 12; ++i) {
        glPushMatrix();
            glRotated(angle * i, 0.0, 0.0, 1.0);
            sazid::drawRectangle(0.435, -0.01, 0.05, 0.02);
        glPopMatrix();
    }
}

void drawMinuteTicks() {
    glColor3ub(54, 54, 54);
    GLdouble angle = 6.0;
    for (int i = 0; i < 60; ++i) {
        glPushMatrix();
            glRotated(angle * i, 0.0, 0.0, 1.0);
            sazid::drawRectangle(0.435, -0.005, 0.02, 0.01);
        glPopMatrix();
    }
}

GLint hourAngle = 30.0;
void drawHourHand() {
    glColor3ub(54, 54, 54);
    glPushMatrix();

        glRotated((-1) * hourAngle * (elaspedTime / 3600) + 90, 0.0, 0.0, 1.0);
        sazid::drawRectangle(0.2, -0.0125, 0.25, 0.025);

    glPopMatrix();
}

GLint minuteAngle = 6.0;
void drawMinuteHand() {
    glColor3ub(54, 54, 54);
    glPushMatrix();

        glRotated((-1) * minuteAngle * (elaspedTime / 60) + 90, 0.0, 0.0, 1.0);
        sazid::drawRectangle(0.335, -0.01, 0.35, 0.02);

    glPopMatrix();
}

GLint secondAngle = 6.0;
void drawSecondHand() {
    glColor3ub(205, 30, 30);
    glPushMatrix();

        glRotated((-1) * secondAngle * elaspedTime + 90, 0.0, 0.0, 1.0);
        sazid::drawRectangle(0.435, -0.005, 0.535, 0.01);

    glPopMatrix();
}

void drawNob() {
    glColor3ub(25, 25, 25);
    sazid::drawCircle(0.0, 0.0, 0.025, 50);
}

void drawClock() {
    drawFrame();
    drawHourTicks();
    drawMinuteTicks();
    drawHourHand();
    drawMinuteHand();
    drawSecondHand();
    drawNob();
}

#pragma region
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
    glClearColor(1, 1, 1, 1.0);
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
#pragma endregion
