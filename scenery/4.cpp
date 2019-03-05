#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();

void createObjects();

void drawSky();
void drawRoad();
void drawMountains();
void drawSun();
void initColors();
void Timer(GLint value);

GLint refreshTimeMillis = 25;

namespace sazid {
    // Draw the string s at the specified position - x, y
    void drawString(GLdouble x, GLdouble y, std::string const& s, void* font);

    // Draw a circle from the given center - cx, cy with radius r
    // steps indicate how smooth the circle will be, greater - smoother
    void drawCircle(GLdouble cx, GLdouble cy, GLfloat r, GLint steps);

    // Draw a rectangle from the given x, y position with width and height - w, h
    void drawRectangle(GLdouble x, GLdouble y, GLdouble w, GLdouble h);
}

class Windmill {
private:
	GLdouble fanAngle = 0.0;
	GLdouble fanSpeed = 1.0;
	GLdouble x;
	GLdouble y;
	GLdouble scale;

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

public:
	Windmill(GLdouble x, GLdouble y) {
		this->x = x;
		this->y = y;
	}

	void setScale(GLdouble scale) {
		this->scale = scale;
	}

	void setSpeed(GLdouble fanSpeed) {
		this->fanSpeed = fanSpeed;
	}

	void update() {
		fanAngle += fanSpeed;
	}

	void draw() {
		glPushMatrix();
		glTranslated(x, y, 0.0);
		glScaled(scale, scale, 0.0);

		glBegin(GL_TRIANGLES);
			glColor3f(0.1f, 0.1f, 0.1f);
			glVertex2f(-0.05f, -0.2f);
			glVertex2f( 0.05f, -0.2f);
			glVertex2f( 0.0f,  0.2f);
		glEnd();


		drawFan(0.0, 0.19, 120.0 + fanAngle);
		drawFan(0.0, 0.19, 240.0 + fanAngle);
		drawFan(0.0, 0.19, 360.0 + fanAngle);

		glPopMatrix();
	}
};

class Car {
private:
    GLdouble x = 0.0;
    GLdouble y = 0.0;
    GLdouble speed = 0.01;
    GLdouble tireSpeed = -5;
    GLdouble tireAngle = 0.0;
    GLdouble scale = 1.0;

    GLubyte color_r;
    GLubyte color_g;
    GLubyte color_b;

    void drawTireWholes(GLdouble x, GLdouble y, GLdouble z, GLdouble angle) {
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(angle, 0.0, 0.0, 1.0);

		sazid::drawCircle(0.0, 0.055, 0.015, 5);
		sazid::drawCircle(0.0, -0.055, 0.015, 5);
		sazid::drawCircle(0.055, 0.0, 0.015, 5);
		sazid::drawCircle(-0.055, 0.0, 0.015, 5);

		glPopMatrix();
	}

public:
	Car(GLdouble x, GLdouble y) {
		this->x = x;
		this->y = y;
	}

	void setPos(GLdouble x, GLdouble y) {
		this->x = x;
		this->y = y;
	}

	void setScale(GLdouble scale) {
		this->scale = scale;
	}

	void setSpeed(GLdouble speed) {
		this->speed = speed;
	}

	void setTireSpeed(GLdouble tireSpeed) {
		this->tireSpeed = tireSpeed;
	}

	void update() {
		x += speed;
		tireAngle += tireSpeed;
		if (x >= 1.5 || x <= -1.5) {
			speed = (-1) * speed;
			tireSpeed = (-1) * tireSpeed;
		}
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b) {
		this->color_r = r;
		this->color_g = g;
		this->color_b = b;
	}

	void draw() {
		glPushMatrix();
		glTranslated(x + speed, y, 0.0);
		glScaled(scale, scale, 0.0);
		glColor3ub(color_r, color_g, color_b);

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
		glColor3ub(240,240,240);
		sazid::drawCircle(0.35, -0.2, 0.1, 100);
		glColor3ub(0,0,0);
		drawTireWholes(0.35, -0.2, 0.0, tireAngle);

		// rear wheel
		glColor3ub(0,0,0);
		sazid::drawCircle(-0.25, -0.2, 0.125, 100);
		glColor3ub(240,240,240);
		sazid::drawCircle(-0.25, -0.2, 0.1, 100);
		glColor3ub(0,0,0);
		drawTireWholes(-0.25, -0.2, 0.0, tireAngle);

		//this->update();

		glPopMatrix();
	}
};

GLubyte colors[3][3];
void initColors() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			colors[i][j] = rand() % 255;
		}
	}
}

Car *car1, *car2, *car3;
Windmill *windmill1, *windmill2, *windmill3, *windmill4;
void createObjects() {
	car1 = new Car(-1.5, 0.05);
	car1->setSpeed(0.02);
	car1->setScale(0.4);
	car1->setTireSpeed(-12);
	car1->setColor(colors[0][0], colors[0][1], colors[0][2]);

	car2 = new Car(-1.0, -0.35);
	car2->setSpeed(0.01);
	car2->setScale(0.6);
	car2->setTireSpeed(-8);
	car2->setColor(colors[1][0], colors[1][1], colors[1][2]);

	car3 = new Car(-1.2, -0.15);
	car3->setSpeed(0.015);
	car3->setScale(0.5);
	car3->setTireSpeed(-10);
	car3->setColor(colors[2][0], colors[2][1], colors[2][2]);

	windmill1 = new Windmill(-0.8, 0.22);
	windmill1->setSpeed(1);
	windmill1->setScale(0.6);

	windmill4 = new Windmill(-0.6, 0.22);
	windmill4->setSpeed(1);
	windmill4->setScale(0.6);

	windmill2 = new Windmill(0.4, 0.3);
	windmill2->setSpeed(2.5);
	windmill2->setScale(1.0);

	windmill3 = new Windmill(0.7, 0.3);
	windmill3->setSpeed(2.5);
	windmill3->setScale(1.0);
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

	// To operate on Model-View matrix
	glMatrixMode(GL_MODELVIEW);
	// Reset the Model-View matrix
	glLoadIdentity();

	drawSky();
    drawSun();
    drawMountains();

	windmill1->draw();
	windmill1->update();

	windmill4->draw();
	windmill4->update();

	windmill2->draw();
	windmill2->update();

	windmill3->draw();
	windmill3->update();

    drawRoad();

	car1->draw();
	car1->update();

	car3->draw();
	car3->update();

	car2->draw();
	car2->update();

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

void drawRoad() {
    glColor3ub(0, 0, 0);
    sazid::drawRectangle(2, 0.1, 4, 0.01);
    sazid::drawRectangle(2, -0.6, 4, 0.01);

    glColor3ub(150, 150, 150);

    for (GLdouble x = -2.0; x <= 2.0; x += 0.45) {
		sazid::drawRectangle(x, -0.25, 0.3, 0.03);
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

