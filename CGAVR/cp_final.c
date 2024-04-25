#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Include this header for usleep function

// Include Guards
#ifndef DIJKSTRA_VISUALIZATION_H
#define DIJKSTRA_VISUALIZATION_H

struct node
{
    int id;
    int xCoordinate;
    int yCoordinate;
} nodes[26], lineNodes[2], sourceNode, destinationNode;

// Global Constants
const float PI = 3.14285714286;
const int maxNodes = 26;
const int radius = 30;

// Global Variables
GLsizei wh = 1020, ww = 1080;
GLfloat size = 3.0;
int nodeCount = 0;
int adjMatrix[26][26];
int lineNodesCount = 0;
int sourceNodeCreated = 0;
int destinationNodeCreated = 0;
int dijkstraRun = 0;
int instruction = 1;

// Added
int pathLength = 0;
int *path = NULL;

// Function Prototypes
void dijkstra();
void myMouse(int btn, int state, int x, int y);
void myReshape(GLsizei w, GLsizei h);
void myInit();
void display_hello();
void myDisplay();
void beginDijkstra(unsigned char key, int x, int y);
void drawCircle(float cx, float cy, float r, float num_segments, char colorCharacter);
void drawLine(char color);
void drawNodesAndEdges();
void drawCar(float x, float y);
void animateCarMovement(int startNode, int endNode, int* path, int pathlength); // Added
void delay(int number_of_seconds);
void fixAdjMatrix();
void routeNodes(int n1, int n2);
int getMinimumDistanceNode(int *distanceFromSource, int *selected);
int computeDistance(struct node a, struct node b);
int noRepeat(int x, int y);
void getPerpendicularCoordinates(int *x, int *y);
void writeDistance(const char *text, int x, int y);
void writeLabel(char text, int x, int y);
void drawSquare(int x, int y);
void getMidPoint(int *midX, int *midY);
int isEdgeInPath(int node1, int node2);

#endif


// Main Function
int main(int argc, char **argv)
{
    fixAdjMatrix();
    printf("SY CSB 24\n\n");
    glutInit(&argc, argv);
    glutInitWindowSize(ww, wh);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Dijksta's Algorithm");
    myInit();
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(beginDijkstra);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}

// Function Definitions
void fixAdjMatrix()
{
    for (int i = 0; i < maxNodes; i++)
    {
        for (int j = 0; j < maxNodes; j++)
        {
            adjMatrix[i][j] = 99999;
        }
    }
}

int computeDistance(struct node a, struct node b)
{
    return (int)sqrt(pow(abs(a.xCoordinate - b.xCoordinate), 2) + pow(abs(a.yCoordinate - b.yCoordinate), 2));
}

int noRepeat(int x, int y)
{
    if (!nodeCount)
        return 1;

    struct node temp = {nodeCount, x, y};

    for (int i = 0; i < nodeCount; i++)
    {
        if (computeDistance(temp, nodes[i]) < 2 * radius)
        {
            lineNodes[lineNodesCount] = nodes[i];
            return 0;
        }
    }
    return 1;
}

void myReshape(GLsizei w, GLsizei h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    ww = w;
    wh = h;
}

void myInit()
{
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ww, 0, wh);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 1);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(5);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_hello();
    glFlush();
}

void display_hello()
{
    writeDistance("SY CSB 24 Simulation of Dijkstra's Algorithm.", 200, 900);
    writeDistance("#  Use Mouse Left Button to Create Nodes.", 250, 800);
    writeDistance("#  Select any two Nodes to form a Path.", 250, 770);
    writeDistance("#  Use Mouse Right Button to select Source and Destination.", 250, 740);
    writeDistance("#  Press ENTER key to begin Dijkstra's Algorithm.", 250, 710);
    writeDistance("Group Members:", 200, 670);
    writeDistance("41 Jannu", 200, 640);
    writeDistance("48 Aniket Kalbhor", 200, 610);
    writeDistance("52 Karan Harshey", 200, 580);
    writeDistance("89 Prutha Pawade", 200, 550);
}

void myMouse(int btn, int state, int x, int y)
{
    if (instruction)
    {
        instruction = 0;
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if (dijkstraRun)
    {
        return;
    }

    y = wh - y;

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (noRepeat(x, y))
        {
            if (nodeCount >= 26)
            {
                return;
            }

            drawCircle(x, y, radius, 200, 'N');
            lineNodesCount = 0;
            nodes[nodeCount].xCoordinate = x;
            nodes[nodeCount].yCoordinate = y;
            nodes[nodeCount].id = nodeCount;
            nodeCount++;
        }
        else
        {
            if (lineNodesCount == 1)
            {
                drawLine('N');
                lineNodesCount = 0;
            }
            else
            {
                lineNodesCount += 1;
            }
        }
    }

    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && (!sourceNodeCreated || !destinationNodeCreated))
    {
        if (nodeCount)
        {
            if (!noRepeat(x, y))
            {
                if (!sourceNodeCreated)
                {
                    sourceNode = lineNodes[0];
                    sourceNodeCreated = 1;
                    drawCircle(sourceNode.xCoordinate, sourceNode.yCoordinate, radius, 200, 'R');
                }
                else
                {
                    if (((sourceNode.xCoordinate - lineNodes[0].xCoordinate) != 0) || ((sourceNode.yCoordinate - lineNodes[0].yCoordinate) != 0))
                    {
                        destinationNode = lineNodes[0];
                        destinationNodeCreated = 1;
                        drawCircle(destinationNode.xCoordinate, destinationNode.yCoordinate, radius, 200, 'B');
                    }
                }
            }
        }
    }
}

void beginDijkstra(unsigned char key, int x, int y)
{
    if (!sourceNodeCreated || !destinationNodeCreated)
    {
        printf("Source node / destination node not selected\n");
        return;
    }
    if ((int)key == 13)
    {
        dijkstraRun = 1;
        dijkstra();
    }
}

void writeDistance(const char *text, int x, int y)
{
    if (instruction)
        glColor3f(1.0, 1.0, 1.0);
    else
        glColor3f(1.0, 1.0, 0.0);
    glRasterPos2i(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glFlush();
}

void drawCircle(float cx, float cy, float r, float num_segments, char colorCharacter)
{
    float theta, x, y;
    if (colorCharacter == 'N')
        writeLabel((char)65 + nodeCount, cx - 5, cy - 14);
    if (colorCharacter == 'N')
        glColor3f(0.0, 1.0, 0.0);
    if (colorCharacter == 'B')
        glColor3f(0.0, 0.0, 1.0);
    if (colorCharacter == 'R')
        glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        theta = 2.0f * PI * i / num_segments;
        x = r * cosf(theta);
        y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
    glFlush();
}

void drawLine(char color)
{
    if (color == 'N' || color == 'R')
        glColor3f(0.3, 0.3, 0.3);
    if (color == 'D')
        glColor3f(0.8, 0.8, 0.8);
    if (color == 'M')
        glColor3f(0.5, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(lineNodes[0].xCoordinate, lineNodes[0].yCoordinate);
    glVertex2f(lineNodes[1].xCoordinate, lineNodes[1].yCoordinate);
    glEnd();
    glFlush();
    int midX, midY;
    char distanceString[10];
    getMidPoint(&midX, &midY);
    int id1 = lineNodes[0].id;
    int id2 = lineNodes[1].id;
    int distance = computeDistance(lineNodes[0], lineNodes[1]);
    adjMatrix[id1][id2] = distance;
    adjMatrix[id2][id1] = distance;
    sprintf(distanceString, "%d", distance);
    getPerpendicularCoordinates(&midX, &midY);
    writeDistance(distanceString, midX, midY);
    glFlush();
    writeLabel('A' + lineNodes[0].id, lineNodes[0].xCoordinate - 5, lineNodes[0].yCoordinate - 14);
    writeLabel('A' + lineNodes[1].id, lineNodes[1].xCoordinate - 5, lineNodes[1].yCoordinate - 14);
    glFlush();
}

void writeLabel(char text, int x, int y)
{
    glColor3f(1.0, 1.0, 0.0);
    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text);
}

void drawSquare(int x, int y)
{
    glBegin(GL_POLYGON);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glEnd();
    glFlush();
}

void getMidPoint(int *midX, int *midY)
{
    *midX = (lineNodes[0].xCoordinate + lineNodes[1].xCoordinate) / 2;
    *midY = (lineNodes[0].yCoordinate + lineNodes[1].yCoordinate) / 2;
}

void getPerpendicularCoordinates(int *x, int *y)
{
    int x1, x2, y1, y2;

    x1 = lineNodes[0].xCoordinate;
    x2 = lineNodes[1].xCoordinate;
    y1 = lineNodes[0].yCoordinate;
    y2 = lineNodes[1].yCoordinate;

    float diff = (x2 - x1) ? 0.0001 : x2 - x1;

    float slope = ((float)(y2 - y1)) / (diff);

    float perpendicularSlope = -1 * (1 / slope);

    *x = *x + 25;
    *y = *y + perpendicularSlope * (*x) + 7;
}

void dijkstra() {
    int distanceFromSource[maxNodes];
    int prev[maxNodes];
    int selected[maxNodes];
    int current;

    // Initialize arrays
    for (int i = 0; i < nodeCount; i++) {
        distanceFromSource[i] = 99999; // Infinity
        prev[i] = -1; // Undefined
        selected[i] = 0; // Not selected
    }

    // Distance from source to itself is 0
    distanceFromSource[sourceNode.id] = 0;

    // Main loop
    for (int i = 0; i < nodeCount; i++) {
        // Select node with minimum distance from source
        current = getMinimumDistanceNode(distanceFromSource, selected);
        if (current == -1) // All reachable nodes are processed
            break;
        selected[current] = 1; // Mark current node as selected

        // Update distance of adjacent nodes
        for (int j = 0; j < nodeCount; j++) {
            if (!selected[j] && adjMatrix[current][j] != 99999) {
                int newDistance = distanceFromSource[current] + adjMatrix[current][j];
                if (newDistance < distanceFromSource[j]) {
                    distanceFromSource[j] = newDistance;
                    prev[j] = current; // Update previous node
                }
            }
        }
    }

    // Obtain the shortest path from Dijkstra's algorithm
    int shortestPathLength = 0; // Initialize the length of the shortest path
    int *shortestPath = NULL; // Initialize the array containing node IDs of the shortest path

    // Find the length of the shortest path
    int currentNode = destinationNode.id;
    while (currentNode != -1 && currentNode != sourceNode.id) {
        shortestPathLength++;
        currentNode = prev[currentNode];
    }
    
    shortestPathLength++;

    // Allocate memory for the shortest path array
    shortestPath = (int *)malloc(shortestPathLength * sizeof(int));
    if (shortestPath == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Fill the shortest path array with node IDs
    currentNode = destinationNode.id;
    for (int i = shortestPathLength - 1; i >= 0; i--) {
        shortestPath[i] = currentNode;
        currentNode = prev[currentNode];
    }
    path = shortestPath;
    pathLength = shortestPathLength;

    // Animate the car movement along the shortest path
    animateCarMovement(sourceNode.id, destinationNode.id, shortestPath, shortestPathLength);

    // Free memory allocated for the shortest path array
    free(shortestPath);
}


int getMinimumDistanceNode(int *distanceFromSource, int *selected)
{
    int minimumNode = -1;
    int minimumDistance = 99999;

    for (int i = 0; i < nodeCount; i++)
    {
        if (selected[i] != 1 && distanceFromSource[i] < minimumDistance)
        {
            minimumDistance = distanceFromSource[i];
            minimumNode = i;
        }
    }
    return minimumNode;
}

void routeNodes(int n1, int n2)
{
    int midX, midY;
    getMidPoint(&midX, &midY);
    drawLine('M');
    char distanceString[10];
    sprintf(distanceString, "%d", adjMatrix[n1][n2]);
    writeDistance(distanceString, midX, midY);
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

// Function to animate car movement between two selected nodes
void animateCarMovement(int startNode, int endNode, int *path, int pathLength) {
    // Number of frames for animation
    int frames = 100;
    // Delay between each frame (in milliseconds)
    int delay = 10;

    // Loop to animate the movement along the specified path
    for (int i = 0; i < pathLength; i++) {
        // Coordinates of the start and end nodes for the current edge
        int startX = nodes[path[i]].xCoordinate;
        int startY = nodes[path[i]].yCoordinate;
        int endX, endY;

        // Check if it's the last node in the path
        if (i == pathLength - 1) {
            // If it's the last node, set the end coordinates to the same as the start node
            endX = startX;
            endY = startY;
        } else {
            // Otherwise, set the end coordinates to the next node in the path
            endX = nodes[path[i + 1]].xCoordinate;
            endY = nodes[path[i + 1]].yCoordinate;
        }

        // Variables to store current position of the car
        float currentX = startX;
        float currentY = startY;

        // Calculate the increment for each frame
        float incrementX = (endX - startX) / (float)frames;
        float incrementY = (endY - startY) / (float)frames;

        // Loop to animate the movement along the current edge
        for (int j = 0; j < frames; j++) {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);
            // Draw the nodes and edges
            drawNodesAndEdges();
            // Draw the car at its current position
            drawCar(currentX, currentY);

            // Update the current position of the car
            currentX += incrementX;
            currentY += incrementY;

            // Flush the buffer to display changes
            glFlush();

            // Add a delay to control the speed of animation
            // Sleep function or equivalent can be used here
            usleep(delay * 1000);
        }
    }
}



// Function to draw the car at a given position
void drawCar(float x, float y) {
    // Set the color of the car
    glColor3f(1.0, 0.0, 0.0);
    // Draw a rectangle representing the car
    glBegin(GL_POLYGON);
    glVertex2f(x - 10, y - 5);
    glVertex2f(x + 10, y - 5);
    glVertex2f(x + 10, y + 5);
    glVertex2f(x - 10, y + 5);
    glEnd();
}

void drawNodesAndEdges() {
    // Draw nodes
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].id == sourceNode.id) {
            // Color source node as red
            drawCircle(nodes[i].xCoordinate, nodes[i].yCoordinate, radius, 200, 'R');
        } else if (nodes[i].id == destinationNode.id) {
            // Color destination node as blue
            drawCircle(nodes[i].xCoordinate, nodes[i].yCoordinate, radius, 200, 'B');
        } else {
            // other nodes
            drawCircle(nodes[i].xCoordinate, nodes[i].yCoordinate, radius, 200, 'N');
        }
    } 

    // Draw edges
    for (int i = 0; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            if (adjMatrix[i][j] != 99999) {
                lineNodes[0] = nodes[i];
                lineNodes[1] = nodes[j];
                if (isEdgeInPath(i, j)) {
                    // Color edges in the path as red
                    drawLine('M');
                } else {
                    // Color other edges as green
                    drawLine('N');
                }
            }
        }
    }
}

// Helper function to check if an edge is in the path being traversed
int isEdgeInPath(int node1, int node2) {
    for (int i = 0; i < pathLength - 1; i++) {
        if ((path[i] == node1 && path[i + 1] == node2) || (path[i] == node2 && path[i + 1] == node1)) {
            return 1;
        }
    }
    return 0;
}
