#include <GL/glut.h>
#include <stdio.h>


int width = 600, height = 600;


void drawPixel(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}


void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
    float color[3];
    getPixelColor(x, y, color);
    if ((color[0] != borderColor[0] || color[1] != borderColor[1] || color[2] != borderColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        drawPixel(x, y, fillColor);
        boundaryFill(x + 1, y, fillColor, borderColor);
        boundaryFill(x - 1, y, fillColor, borderColor);
        boundaryFill(x, y + 1, fillColor, borderColor);
        boundaryFill(x, y - 1, fillColor, borderColor);
    }
}


void drawTriangle() {
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    glBegin(GL_POLYGON);
    glVertex2i(300, 100);
    glVertex2i(450, 300);
    glVertex2i(200, 400);
    glEnd();
}


void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float borderColor[3] = { 0.0f, 0.0f, 1.0f }; // Set border color to blue
        float fillColor[3] = { 1.0f, 0.0f, 0.0f }; 
        boundaryFill(x, height - y, fillColor, borderColor); 
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width, 0, height);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle(); 
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}