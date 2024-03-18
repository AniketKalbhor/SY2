#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>

GLsizei window_height = 1020, window_width = 1080;
GLfloat size = 3.0; //Used in drawSquare, square length
float PI = 3.14285714286;
int radius = 30;
int nodeCount = 0;
int maxNodes = 26;
int adjMatrix[26][26];
int lineNodesCount = 0; //No. of nodes selected to draw a line
int sourceNodeCreated = 0;
int destinationNodeCreated = 0;
int instruction = 1; //instruction display

struct node
{	
    int id;
    int xCoordinate;
    int yCoordinate;
}nodes[26], lineNodes[2], sourceNode, destinationNode;

int computeDistance(struct node a, struct node b){
    return (int) sqrt(pow(abs(a.xCoordinate - b.xCoordinate), 2) + pow(abs(a.yCoordinate - b.yCoordinate), 2));
}

//Check if two nodes intersect i.e if to create a new node or select a node 
int noRepeat(int x, int y) {	
    if(!nodeCount)
        return 1;

    //create a temp node for comparison on the clicked coordinate
    struct node temp = {nodeCount, x, y};

    for(int i = 0; i < nodeCount; i++)
    {	
        //if the nodes intersect, assume a node is clicked
        if(computeDistance(temp, nodes[i]) < 2*radius)
        {	 
            //push the clicked node to the stack
            lineNodes[lineNodesCount] = nodes[i];
            return 0;
        }
    }
    //no node was pressed, create a new node at x,y
    return 1;
}

//write Distance between the nodes to screen
void writeDistance(char *text, int x, int y)
{	
    if(instruction)
        glColor3f(1.0, 1.0, 1.0);
    else
        glColor3f(1.0, 1.0, 0.0);
    glRasterPos2i(x,y);
    int len = strlen(text);
    for(int i = 0; i < len; i++)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18 , text[i]);
    glFlush();
}

void writeLabel(char text, int x, int y)
{	
    glColor3f(1.0, 1.0, 0.0); //yellow
    glRasterPos2i(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , text);
}

void drawCircle(float cx, float cy, float r, float num_segments, char colorCharacter)
{
    //theta- angle in radians of the point 
    //x- x coordinate of point
    //y- y coordinate of point
    float theta,x,y;

    if(colorCharacter == 'N') //Give the center of the circle a label [A-Z]
        writeLabel((char)65 + nodeCount ,cx - 5, cy - 14);
    if(colorCharacter == 'N') //its node
        glColor3f(0.0, 1.0, 0.0);
    if(colorCharacter == 'B') //its destination
        glColor3f(0.0, 0.0, 1.0);
    if(colorCharacter == 'R') //its source
        glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
 
    for(int i = 0; i < num_segments; i++){
        //compute new angle and get the x, y coordinate
        theta = 2.0f * PI * i / num_segments;
 		x = r * cosf(theta);
        y = r * sinf(theta);
 		
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
    glFlush();

}

void getMidPoint(int *midX, int *midY){
    *midX = (lineNodes[0].xCoordinate + lineNodes[1].xCoordinate)/2;
    *midY = (lineNodes[0].yCoordinate + lineNodes[1].yCoordinate)/2;
}

void drawLine(char color) {
    glColor3f(0.3, 0.3, 0.3);
    //draw lines between selected nodes (stored in lineNodes)
    glBegin(GL_LINES);
        glVertex2f(lineNodes[0].xCoordinate, lineNodes[0].yCoordinate);
        glVertex2f(lineNodes[1].xCoordinate, lineNodes[1].yCoordinate);
    glEnd();
    glFlush();

    //Mid Point of the line segment to display distance
    int midX, midY;
    char distanceString[10]; 
    getMidPoint(&midX, &midY);  

    //get nodes id, keys for the adjMatrix 
    int id1 = lineNodes[0].id;
    int id2 = lineNodes[1].id;
    int distance = computeDistance(lineNodes[0], lineNodes[1]);
    adjMatrix[id1][id2] = distance;
    adjMatrix[id2][id1] = distance;

    //Convert distance to string
    sprintf(distanceString, "%d",distance);
    writeDistance(distanceString, midX, midY);
    glFlush();

    //write both circles' labels again to make them visible after the line is drawn
    writeLabel('A' + lineNodes[0].id, lineNodes[0].xCoordinate - 5, lineNodes[0].yCoordinate - 14);
    writeLabel('A' + lineNodes[1].id, lineNodes[1].xCoordinate - 5, lineNodes[1].yCoordinate - 14);
    glFlush();
}


void myMouse(int btn, int state, int x, int y) 
{
    //Clear Instructions first
    if(instruction)
    {
        instruction = 0;
        glClear(GL_COLOR_BUFFER_BIT);
    }
    y = window_height-y; //fix coordinate system for mouse to work

    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) //left click: create nodes, join nodes
    {	
        //if not clicked on the circle 
        if (noRepeat(x, y))
        {
            if(nodeCount >= 26)
                return;

            drawCircle(x, y, radius, 200, 'N');
            lineNodesCount = 0;
            nodes[nodeCount].xCoordinate = x;
            nodes[nodeCount].yCoordinate = y;
            nodes[nodeCount].id = nodeCount;
            nodeCount++;
        } 
        else
        {
            if(lineNodesCount == 1)
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

    //right click: select source and destination nodes
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN && (!sourceNodeCreated || !destinationNodeCreated))
    {
        //if nodes are created
        if(nodeCount)
        {	
            //if a node is clicked, lineNodes[0] will have the node clicked
            if(!noRepeat(x, y))
            {
                //if source node is not assigned
                if(!sourceNodeCreated)
                {
                    sourceNode = lineNodes[0];
                    //source node created
                    sourceNodeCreated = 1;
                    //change color of the source node to (R)ed
                    drawCircle(sourceNode.xCoordinate, sourceNode.yCoordinate, radius, 200, 'R');
                }
                else 
                {
                    //first, check if source is not selected again
                    if(((sourceNode.xCoordinate - lineNodes[0].xCoordinate) != 0) || ((sourceNode.yCoordinate - lineNodes[0].yCoordinate) != 0 ))
                    {
                        destinationNode = lineNodes[0];
                        //destination node created
                        destinationNodeCreated = 1;
                        //change color of the destination node to (B)lue
                        drawCircle(destinationNode.xCoordinate, destinationNode.yCoordinate, radius, 200, 'B');
                    } 
                }

            }
        }
    }

}

void myInit()
{
    glViewport(0,0,window_width,window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 1);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(5);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void initAdjMatrix()
{
    for(int i = 0; i < maxNodes; i++)
        for(int j = 0; j < maxNodes; j++)
            adjMatrix[i][j] = 99999;
}

int main(int argc, char **argv) 
{
    initAdjMatrix();
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Dijksta's Algorithm");
    myInit();
    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}