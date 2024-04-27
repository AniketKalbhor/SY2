#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Window Size
GLsizei wh = 1020, ww = 1080;

// Used in drawSquare, square length
GLfloat size = 3.0;

float PI = 3.14285714286;

// Radius of circle
int radius = 30;

// No. of nodes in window
int nodeCount = 0;

// Max No. of nodes that can be created
int maxNodes = 26;

// 2X2 matrix between the nodes
int adjMatrix[26][26];

// No. of nodes selected to draw a line
int lineNodesCount = 0;

// Source node created
int sourceNodeCreated = 0;

// Destination node created
int destinationNodeCreated = 0;

// Dijkstra begin
int dijkstraRun = 0;

// instruction display
int instruction = 1;

// Create node struct
struct node
{
    int id;
    int xCoordinate;
    int yCoordinate;
} nodes[26], lineNodes[2], sourceNode, destinationNode;

// Return distance between two nodes
int computeDistance(struct node a, struct node b)
{
    return (int)sqrt(pow(abs(a.xCoordinate - b.xCoordinate), 2) + pow(abs(a.yCoordinate - b.yCoordinate), 2));
}

// Check if two nodes intersect i.e if to create a new node or select a node
int noRepeat(int x, int y)
{
    // if no nodes on screen, don't bother
    if (!nodeCount)
        return 1;

    // create a temp node for comparison on the clicked coordinate
    struct node temp = {nodeCount, x, y};

    for (int i = 0; i < nodeCount; i++)
    {
        // if the nodes intersect, assume a node is clicked
        if (computeDistance(temp, nodes[i]) < 2 * radius)
        {
            // push the clicked node to the stack
            lineNodes[lineNodesCount] = nodes[i];
            return 0;
        }
    }
    // no node was pressed, create a new node at x,y
    return 1;
}

// Get perpendicular coordinates to display the text
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

// Write Distance between the nodes to screen
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

// Write Label to nodes to screen
void writeLabel(char text, int x, int y)
{
    // change the color to yellow
    glColor3f(1.0, 1.0, 0.0);
    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text);
}

// Draw Circle at the given coordinates
void drawCircle(float cx, float cy, float r, float num_segments, char colorCharacter)
{
    float theta, x, y;

    // Give the center of the circle a label [A-Z]
    if (colorCharacter == 'N')
        writeLabel((char)65 + nodeCount, cx - 5, cy - 14);

    // Change the color to green if colorCharacter = 'N'
    if (colorCharacter == 'N')
        glColor3f(0.0, 1.0, 0.0);

    if (colorCharacter == 'B')
        glColor3f(0.0, 0.0, 1.0);

    if (colorCharacter == 'R')
        glColor3f(1.0, 0.0, 0.0);

    // Line loop- connect all the points below
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < num_segments; i++)
    {
        // Compute new angle and get the x, y coordinate
        theta = 2.0f * PI * i / num_segments;
        x = r * cosf(theta);
        y = r * sinf(theta);

        // Draw the point
        glVertex2f(x + cx, y + cy);
    }
    glEnd();

    // Flush to output screen
    glFlush();
}

// Draw square
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

// Sets the mid point coordinates to the arguments
void getMidPoint(int *midX, int *midY)
{
    *midX = (lineNodes[0].xCoordinate + lineNodes[1].xCoordinate) / 2;
    *midY = (lineNodes[0].yCoordinate + lineNodes[1].yCoordinate) / 2;
}

// Draw lines between two nodes
void drawLine(char color)
{
    // Set color to white
    if (color == 'N' || color == 'R')
        glColor3f(0.3, 0.3, 0.3);

    if (color == 'D')
        glColor3f(0.8, 0.8, 0.8);

    if (color == 'M')
        glColor3f(0.5, 0.0, 0.0);

    // Draw lines between selected nodes (stored in lineNodes)
    glBegin(GL_LINES);
    glVertex2f(lineNodes[0].xCoordinate, lineNodes[0].yCoordinate);
    glVertex2f(lineNodes[1].xCoordinate, lineNodes[1].yCoordinate);
    glEnd();
    glFlush();

    // Mid Point of the line segment to display distance
    int midX, midY;
    char distanceString[10];
    // Get the mid coordinates
    getMidPoint(&midX, &midY);

    // Get nodes id, keys for the adjMatrix
    int id1 = lineNodes[0].id;
    int id2 = lineNodes[1].id;
    // Compute distance between the nodes.
    int distance = computeDistance(lineNodes[0], lineNodes[1]);
    // Store it in adjMatrix
    adjMatrix[id1][id2] = distance;
    adjMatrix[id2][id1] = distance;

    // Convert distance to string
    sprintf(distanceString, "%d", distance);
    // Display to the window
    getPerpendicularCoordinates(&midX, &midY);
    writeDistance(distanceString, midX, midY);

    // Write both circles' labels again
    writeLabel('A' + lineNodes[0].id, lineNodes[0].xCoordinate - 5, lineNodes[0].yCoordinate - 14);
    writeLabel('A' + lineNodes[1].id, lineNodes[1].xCoordinate - 5, lineNodes[1].yCoordinate - 14);
}

// Mouse click handler
void myMouse(int btn, int state, int x, int y)
{
    // Clear Instructions first
    if (instruction)
    {
        instruction = 0;
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Don't listen to mouse events if dijkstra operation is running
    if (dijkstraRun)
    {
        return;
    }

    // Fix coordinate system
    y = wh - y;

    // Left click: create nodes, join nodes
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // if not clicked on the circle
        if (noRepeat(x, y))
        {
            // Don't draw if nodeCount > 26;
            if (nodeCount >= 26)
            {
                return;
            }

            // Draw new circle
            drawCircle(x, y, radius, 200, 'N');
            lineNodesCount = 0;
            // Set the values of the new node
            nodes[nodeCount].xCoordinate = x;
            nodes[nodeCount].yCoordinate = y;
            nodes[nodeCount].id = nodeCount;

            // Increase the node count
            nodeCount++;
        }
        // Draw line
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

    // Right click: select source and destination nodes
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && (!sourceNodeCreated || !destinationNodeCreated))
    {
        // if nodes are created
        if (nodeCount)
        {
            // if a node is clicked, lineNodes[0] will have the node clicked
            if (!noRepeat(x, y))
            {
                // if source node is not assigned
                if (!sourceNodeCreated)
                {
                    sourceNode = lineNodes[0];
                    // Source node created
                    sourceNodeCreated = 1;
                    // Change color of the source node to (R)ed
                    drawCircle(sourceNode.xCoordinate, sourceNode.yCoordinate, radius, 200, 'R');
                }
                else
                {
                    // first, check if source is not selected again
                    if (((sourceNode.xCoordinate - lineNodes[0].xCoordinate) != 0) || ((sourceNode.yCoordinate - lineNodes[0].yCoordinate) != 0))
                    {
                        destinationNode = lineNodes[0];
                        // Destination node created
                        destinationNodeCreated = 1;
                        // Change color of the destination node to (B)lue
                        drawCircle(destinationNode.xCoordinate, destinationNode.yCoordinate, radius, 200, 'B');
                    }
                }
            }
        }
    }
}

// MyReshape to Handle change in window size
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

// Window initialization
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

// Function to display instructions
void display_hello()
{
    writeDistance(" Welcome! To The Simulation of Dijkstra's Algorithn.", 200, 900);
    writeDistance("#  Use Mouse Left Button to Create Nodes.", 250, 800);
    writeDistance("#  Select any two Nodes to form a Path.", 250, 770);
    writeDistance("#  Use Mouse Right Button to select Source and Destination.", 250, 740);
    writeDistance("#  Press ENTER key to begin Dijkstra's Algorithm.", 250, 710);
}

// Display function
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_hello();
    glFlush();
}

// Fix adjacency matrix: set the distance among the nodes to highest value (99999)
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

// Main function
int main(int argc, char **argv)
{
    fixAdjMatrix();
    glutInit(&argc, argv);
    glutInitWindowSize(ww, wh);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Dijksta's Algorithm");
    myInit();
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
