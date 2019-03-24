//#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <bits/stdc++.h>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void specialKeyDown(int, int, int);
void specialKeyUp(int, int, int);

void createObjects();

void drawSky();
void drawMonument();
void initColors();
void Timer(GLint value);

std::default_random_engine re;
GLint refreshTimeMillis = 16;

namespace sazid {
    // Draw the string s at the specified position - x, y
    void drawString(GLdouble x, GLdouble y, std::string const& s, void* font);

    // Draw a circle from the given center - cx, cy with radius r
    // steps indicate how smooth the circle will be, greater - smoother
    void drawCircle(GLdouble cx, GLdouble cy, GLfloat r, GLint steps);

    // Draw a rectangle from the given x, y position with width and height - w, h
    void drawRectangle(GLdouble x, GLdouble y, GLdouble w, GLdouble h);
}

GLubyte colors[3][3];
void initColors() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 3; ++j) {
			colors[i][j] = rand() % 255;
		}
	}

}

class Rain {
private:
    GLdouble left, right, bottom, top;
	GLdouble *x, *y;
	GLdouble angle;
	GLdouble speed;
	GLint particle_count;

	std::uniform_real_distribution<GLdouble> *urd_horizontal, *urd_vertical;

	void initParticles() {
        for (int i = 0; i < particle_count; ++i) {
            x[i] = (*urd_horizontal)(re);
            y[i] = (*urd_vertical)(re);
        }
	}

public:
	Rain(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble angle, GLdouble speed, GLint particle_count) {
		this->angle = angle;
		this->speed = speed;
		this->particle_count = particle_count;

		urd_horizontal = new std::uniform_real_distribution<GLdouble>(left, right);
		urd_vertical = new std::uniform_real_distribution<GLdouble>(bottom, top);

		x = new GLdouble[particle_count];
		y = new GLdouble[particle_count];

		initParticles();
	}

	~Rain() {
        delete urd_horizontal;
        delete urd_vertical;

        delete[] x;
        delete[] y;
	}

	void setAngle(GLdouble angle) {
		this->angle = angle;
	}


    void update() {
        for (int i = 0; i < particle_count; ++i) {
            if (y[i] < bottom) {
                y[i] = (*urd_vertical)(re);
            }

            y[i] -= speed;
        }
	}

	void draw() {
	    for (int i = 0; i < particle_count; ++i) {
            glPushMatrix();
            glRotated(angle, 0, 0, 1);
            glTranslated(x[i], y[i], 0.0);

            glBegin(GL_QUADS);
                glVertex2f( 0.005f, -0.03f);
                glVertex2f( 0.005f,  0.03f);
                glVertex2f(-0.005f,  0.03f);
                glVertex2f(-0.005f,  -0.03f);
            glEnd();

            glPopMatrix();
	    }
	}
};

Rain *rain;
void createObjects() {
	rain = new Rain(-2, 2, -5, 5, 0, 0.02, 250);
}

int main(int argc, char **argv) {
    // Initialize glut
    glutInit(&argc, argv);

    // Set display mode
    // GLUT_DOUBLE - enable double buffering
    // GLUT_RGBA - RGBA color for display
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    // Set window size
    glutInitWindowSize(500, 500);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("Assignment 3 | 17-33330-1");

    // Initialize OpenGL
    initOpenGL();

	initColors();

    // Initialize objects
    createObjects();

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
    glutTimerFunc(refreshTimeMillis, Timer, 0);
}

void display() {
    // Use the preset color (using glClearColor) to redraw the color buffer
    // Call this to clear the current buffer and start anew
    glClear(GL_COLOR_BUFFER_BIT);

    gluOrtho2D(-2, 2, -2, 2);

	// To operate on Model-View matrix
	glMatrixMode(GL_MODELVIEW);
	// Reset the Model-View matrix
	glLoadIdentity();

	drawSky();
    drawMonument();

	glColor3ub(100, 100, 100);
	rain->draw();
	rain->update();

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
    glClearColor(0.25, 0.25, 0.25, 1.0);
	initColors();
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

void drawSky() {
    glPushMatrix();
        glTranslated(0.0, 0.1, 0.0);

        glBegin(GL_QUADS);
            glColor3ub(110, 215, 255);
            glVertex2d(5.0, 0.0);
            glVertex2d(5.0, 5.0);

            glColor3ub(110, 215, 255);
            glVertex2d(-5.0, 5.0);
            glVertex2d(-5.0, 0.0);
        glEnd();
    glPopMatrix();
}

std::uniform_real_distribution<GLdouble> urd(0.0, 0.2);

void drawMonument() {
    glPushMatrix();
    glTranslated(0.0, 0.1, 0);

    glColor3ub(248, 50, 0);
    sazid::drawCircle(1.3, 1.3, 0.25, 100);


    GLdouble x = 1.2;
    GLdouble y = 0.3;

    GLubyte r = 90, g = 90, b = 90;

    for (int i = 1; i <= 5; ++i) {
        glColor3ub(r, g, b);
        glBegin(GL_TRIANGLES);

            glVertex2d(-x, 0);
            glVertex2d(x, 0);
            glVertex2d(0, y);

        glEnd();

        x -= 0.25;
        y += 0.25;

        r += 10;
        g += 10;
        b += 10;
    }

    glColor3ub(90, 90, 90);
    glBegin(GL_TRIANGLES);

        glVertex2d(-0.1, 0.4);
        glVertex2d(0.1, 0.4);
        glVertex2d(0, 0.7);

        glVertex2d(-0.1, 0.4);
        glVertex2d(0.1, 0.4);
        glVertex2d(0, 0.15);

    glEnd();

    /*glBegin(GL_QUADS);

        glVertex2d(0, 0);
        glVertex2d(0, 0.2);
        glVertex2d(-0.2, 0.2);
        glVertex2d(-0.2, 0);

    glEnd();*/

    glPopMatrix();
}
