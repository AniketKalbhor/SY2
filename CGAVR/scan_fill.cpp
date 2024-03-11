#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

int le[500], re[500], flag = 0, m;
int fillPolygon = 0;

void init()
{
    gluOrtho2D(0, 500, 0, 500);
}

void edge(int x0, int y0, int x1, int y1)
{
    if (y1 < y0)
    {
        int tmp;
        tmp = y1;
        y1 = y0;
        y0 = tmp;
        tmp = x1;
        x1 = x0;
        x0 = tmp;
    }
    int x = x0;
    m = (y1 - y0) / 1;
    for (int i = y0; i < y1; i++)
    {
        if (x < le[i])
            le[i] = x;
        if (x > re[i])
            re[i] = x;
        x += (1 / m);
    }
}

void drawPixel(int x, int y) {
    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void scanFill() {
    for (int i = 0; i < 500; i++)
    {
        if (le[i] < re[i])
        {
            for (int j = le[i]; j < re[i]; j++)
            {
                drawPixel(j, i);
            }
        }
    }
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(100, 100);
    glVertex2f(100, 400);
    glVertex2f(400, 400);
    glVertex2f(400, 100);
    glEnd();

    for (int i = 0; i < 500; i++)
    {
        le[i] = 500;
        re[i] = 0;
    }
    edge(100, 100, 100, 400);
    edge(100, 100, 100, 400);
    edge(100, 400, 400, 400);
    edge(400, 400, 400, 100);
    edge(400, 100, 100, 100);

    if (fillPolygon == 1)
    {
        scanFill();
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        fillPolygon = 1;
        glutPostRedisplay();
    }
}

void ScanMenu(int id) {
    if (id == 1)
        fillPolygon = 1;
    else if (id == 2)
        fillPolygon = 0;
    else
        exit(0);

    
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("scan line");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(ScanMenu);
    glutAddMenuEntry("Fill", 1);
    glutAddMenuEntry("Clear", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}