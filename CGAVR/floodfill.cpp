#include <GL/glut.h>

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void floodFill(int x, int y, float fillColor[3], float borderColor[3])
{
    float interiorColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);

    if (
        (interiorColor[0] != borderColor[0] || interiorColor[1] != borderColor[1] || interiorColor[2] != borderColor[2]) &&
        (interiorColor[0] != fillColor[0] || interiorColor[1] != fillColor[1] || interiorColor[2] != fillColor[2])
    )
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y, fillColor, borderColor);
        floodFill(x - 1, y, fillColor, borderColor);
        floodFill(x, y + 1, fillColor, borderColor);
        floodFill(x, y - 1, fillColor, borderColor);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(400, 100);
    glVertex2i(400, 400);
    glVertex2i(100, 400);
    glEnd();
    glFlush();

    float fillColor[] = {0.0, 1.0, 0.0};    
    float borderColor[] = {1.0, 1.0, 1.0};  
    floodFill(250, 250, fillColor, borderColor);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Flood Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
