#include <stdio.h>
#include <GL/glut.h>

int width = 800, height = 600;
float object[4][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}};
float temp[4][2];

void drawObject(float temp[4][2]) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
        glVertex2f(temp[i][0], temp[i][1]);
    }
    glEnd();
}

// void handleKey(unsigned char key, int x, int y) {
//     float shx = 0.5;
//     float shy = 0.0;
//     switch (key) {
//         case 'a': //shearing
//             for (int i = 0; i < 4; i++) {
//                 temp[i][0] = object[i][0] + object[i][1] * shx;
//                 temp[i][1] = object[i][1] + object[i][0] * shy;
//             }
//             drawObject(temp);
//             break;
//         case 's': //scaling
//             for (int i = 0; i < 4; i++) {
//                 temp[i][0] = object[i][0] * 0.5;
//                 temp[i][1] = object[i][1] * 0.5;
//             }
//             break;
//         case 'd': //translation
//             break;
//         case 'f': 
//             break;
//         case 'g': 
//             break;
//         case 27:
//             exit(0);
//             break;
//     }
//     glutPostRedisplay();
// }

void handleResize(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glColor3f(1.0, 0.0, 0.0);
    drawObject(object);
    
    glFlush();
    glutSwapBuffers();
}

int handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        printf("Mouse clicked at (%d, %d)\n", x, y);
        return 1;
    }
}

void menu(){
    int choice;
    float shx = 0.5;
    float shy = 0.0;
    if ((GLUT_LEFT_BUTTON, GLUT_DOWN, 0, 0));
    {
        printf("1. Shearing\n");
        for (int i = 0; i < 4; i++) {
            temp[i][0] = object[i][0] + object[i][1] * shx;
            temp[i][1] = object[i][1] + object[i][0] * shy;
        }
        drawObject(temp);
    }
    printf("2. Scaling\n");    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("2D Transformation");
    
    glutDisplayFunc(display);
    // glutKeyboardFunc(handleKey);
    menu();
    glutReshapeFunc(handleResize);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glutMainLoop();
    
    return 0;
}