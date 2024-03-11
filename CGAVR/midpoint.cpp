#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h>

void drawCircleMidpoint(float xc, float yc, float radius) {
    float x = radius;
    float y = 0;
    float err = 0;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    while (x >= y) {
        glVertex2f(xc + x, yc + y);
        glVertex2f(xc - x, yc + y);
        glVertex2f(xc + x, yc - y);
        glVertex2f(xc - x, yc - y);
        glVertex2f(xc + y, yc + x);
        glVertex2f(xc - y, yc + x);
        glVertex2f(xc + y, yc - x);
        glVertex2f(xc - y, yc - x);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Example: Draw a circle using midpoint algorithm with center (400, 300) and radius 100
    drawCircleMidpoint(400, 300, 100);

    glFlush();
}

int main(int argc, char* argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set the window size
    glutInitWindowSize(800, 600);

    // Create the window with the title "Hello, GL"
    glutCreateWindow("Hello, GL");

    // Set the viewport
    glViewport(0, 0, 800, 600);

    // Set the coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    // Bind the display function to respond when necessary
    glutDisplayFunc(display);

    // To avoid the window from being closed
    glutMainLoop();
    return 0;
}