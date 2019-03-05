#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void drawRoad();
void drawCar();
void drawMountains();
void drawSun();

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

    drawSun();
    drawMountains();
    drawRoad();
    drawCar();

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
GLdouble addFactor = 0.001;

void drawCar() {
    glColor3ub(10,100,100);
    sazid::drawRectangle(x+0.4, -0.2, 0.8, 0.4);

    glBegin(GL_QUADS);

        // front bumper
        glVertex2d(x+0.55, -0.2);
        glVertex2d(x+0.55, -0.05);
        glVertex2d(x+0.4, 0.2);
        glVertex2d(x+0.4, -0.2);

        // rear spoiler
        glVertex2d(x-0.4, -0.2);
        glVertex2d(x-0.4, 0.2);
        glVertex2d(x-0.48, 0.22);
        glVertex2d(x-0.48, -0.2);

        // top hood
        glVertex2d(x+0.2, 0.2);
        glVertex2d(x+0.15, 0.23);
        glVertex2d(x-0.15, 0.23);
        glVertex2d(x-0.2, 0.2);

        glColor3ub(50,50,50);

        // rear window
        glVertex2d(x-0.01, -0.02);
        glVertex2d(x-0.01, 0.15);
        glVertex2d(x-0.35, 0.15);
        glVertex2d(x-0.35, -0.02);

        // front window
        glVertex2d(x+0.4, -0.02);
        glVertex2d(x+0.3, 0.15);
        glVertex2d(x+0.03, 0.15);
        glVertex2d(x+0.03, -0.02);

    glEnd();

    // front wheel
    glColor3ub(0, 0, 0);
    sazid::drawCircle(x+0.35, -0.2, 0.125, 100);
    glColor3ub(50,50,50);
    sazid::drawCircle(x+0.35, -0.2, 0.1, 100);
    // rear wheel
    glColor3ub(0,0,0);
    sazid::drawCircle(x-0.25, -0.2, 0.125, 100);
    glColor3ub(50,50,50);
    sazid::drawCircle(x-0.25, -0.2, 0.1, 100);

    x += addFactor;
    if (x >= 1.5 or x <= -1.5) {
        addFactor = (-1) * addFactor;
    }
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

