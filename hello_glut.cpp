#include <GL/glut.h>
#include <iostream>

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();

int main(int argc, char **argv) {
    // Initialize glut
    glutInit(&argc, argv);

    // Set display mode
    // GLUT_DOUBLE - enable double buffering
    // GLUT_DEPTH - depth information for 3d
    // GLUT_RGBA - RGBA color for display
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // Set window size
    glutInitWindowSize(500, 500);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("First OpenGL App");

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

    // Call glBegin(...) here to start drawing

    // Call glEnd() here to stop drawing

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
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

