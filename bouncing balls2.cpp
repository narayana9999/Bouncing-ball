#include <Math.h>
#include <iostream>
#include<GL/freeglut.h>
#include <windows.h>
using namespace std;

const float PI = 3.14159265f;

const int numBalls=9; // number of bouncing balls
GLfloat ballRadius = 0.1f;
GLfloat ballX[numBalls], ballY[numBalls];
GLfloat ballXMax[numBalls], ballXMin[numBalls], ballYMax[numBalls], ballYMin[numBalls];
GLfloat xSpeed[numBalls], ySpeed[numBalls];
GLfloat xAcceleration[numBalls], yAcceleration[numBalls];
bool isPaused = false;
int refreshMillis = 16;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);    
     
}
void display()
{
    if (isPaused) return;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < numBalls; i++)
    {
        glPushMatrix();
        glTranslatef(ballX[i], ballY[i], 0.0f);
        glBegin(GL_TRIANGLE_FAN); //for creating a ball
        glColor3f((GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX); // use random RGB values for each ball
        glVertex2f(0.0f, 0.0f);
        int numSegments = 100;
        GLfloat angle;
        for (int j = 0; j <= numSegments; j++)
        {
            angle = j * 2.0f * PI / numSegments;
            glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
        }
        glEnd();
        glPopMatrix();
    }

    glutSwapBuffers();   //glutSwapBuffers promotes the contents of the back buffer of the layer in use of the current window to become the contents of the front buffer. 

    for (int i = 0; i < numBalls; i++)
    {
        xSpeed[i] += xAcceleration[i];
        ySpeed[i] += yAcceleration[i];
        ballX[i] += xSpeed[i];
        ballY[i] += ySpeed[i];
        if (ballX[i] > ballXMax[i])
        {
            ballX[i] = ballXMax[i];
            xSpeed[i] = -xSpeed[i];
        }
        else if (ballX[i] < ballXMin[i])
        {
            ballX[i] = ballXMin[i];
            xSpeed[i] = -xSpeed[i];
        }
        if (ballY[i] > ballYMax[i])
        {
            ballY[i] = ballYMax[i];
            ySpeed[i] = -ySpeed[i];
        }
        else if (ballY[i] < ballYMin[i])
        {
            ballY[i] = ballYMin[i];
            ySpeed[i] = -ySpeed[i];
        }
    }
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width >= height)
    {
        clipAreaXLeft = -1.0 * aspect;
        clipAreaXRight = 1.0 * aspect;
        clipAreaYBottom = -1.0 * (GLfloat)height / (GLfloat)width;
        clipAreaYTop = 1.0 * aspect * (GLfloat)height / (GLfloat)width;
}
glOrtho(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop, -1.0, 1.0);
}

void timer(int value)
{
glutPostRedisplay();
glutTimerFunc(refreshMillis, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
switch (key)
{
case 27: // ESC key
exit(0);
break;
case 'p':
    isPaused = !isPaused;
    break;

default:
    break;
}
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE);
glutInitWindowSize(640, 480);
glutInitWindowPosition(50, 50);
glutCreateWindow("Bouncing Balls");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(0, timer, 0);
glutKeyboardFunc(keyboard);
init();
for (int i = 0; i < numBalls; i++)
{
ballX[i] = (GLfloat)rand() / (GLfloat)RAND_MAX * 2.0f - 1.0f;
ballY[i] = (GLfloat)rand() / (GLfloat)RAND_MAX * 2.0f - 1.0f;
xSpeed[i] = (GLfloat)rand() / (GLfloat)RAND_MAX * 0.02f - 0.01f;
ySpeed[i] = (GLfloat)rand() / (GLfloat)RAND_MAX * 0.02f - 0.01f;
xAcceleration[i] = 0.0f;
yAcceleration[i] = -0.00005f;
ballXMax[i] = 1.0f - ballRadius;
ballXMin[i] = -1.0f + ballRadius;
ballYMax[i] = 1.0f - ballRadius;
ballYMin[i] = -1.0f + ballRadius;
glColor3f((GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX, (GLfloat)rand() / RAND_MAX); // use random RGB values for each ball
}
glutMainLoop();
return 0;
}

