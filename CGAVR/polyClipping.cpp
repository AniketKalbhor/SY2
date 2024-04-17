#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define MAX_VERTICES 100

int num_vertices = 0;
int clipping_window_defined = 0;
int win_width = 800, win_height = 600;
int clip_xmin, clip_ymin, clip_xmax, clip_ymax;
int polygon_clipped = 0;

typedef struct {
    int x, y;
} Point;

Point vertices[MAX_VERTICES];
Point clipped_vertices[MAX_VERTICES];

void drawPolygon() {
    if (num_vertices < 2)
        return;

    glColor3f(0.0, 0.0, 0.0); // Black color for original polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_vertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

void drawClippingWindow() {
    if (!clipping_window_defined)
        return;

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(clip_xmin, clip_ymin);
    glVertex2i(clip_xmax, clip_ymin);
    glVertex2i(clip_xmax, clip_ymax);
    glVertex2i(clip_xmin, clip_ymax);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygon();
    drawClippingWindow();

    if (clipping_window_defined && polygon_clipped) {
        clipPolygon();
    }

    glColor3f(1.0, 0.0, 0.0); // Red color for clipped polygon
    glBegin(GL_POLYGON); // Use GL_POLYGON to render a filled polygon
    for (int i = 0; i < num_vertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();

    glFlush();
{}


void keyboard(unsigned char key, int x, int y) {
    if (key == 13) { // Enter key
        polygon_clipped = 1;
        glutPostRedisplay();
    }

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!clipping_window_defined) {
            // Define clipping window
            clip_xmin = x;
            clip_ymin = win_height - y;
            clipping_window_defined = 1;
        } else if (!polygon_clipped) {
            // Add vertex to polygon
            vertices[num_vertices].x = x;
            vertices[num_vertices].y = win_height - y;
            num_vertices++;
        }
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, win_width, 0, win_height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
