#include <iostream>
#include <GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>
#include <GL/gl.h>
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif
#include <math.h>
#include <cstdlib>

using namespace std;

const int width = 1200;
const int height = 1000;
int t = 10;

GLfloat eyeX = 50;
GLfloat eyeY = 25;
GLfloat eyeZ = 50 + 20 + 25 + 20 + 6;

GLfloat lookX = 50;
GLfloat lookY = 0 + 20;
GLfloat lookZ = 20;

static GLfloat v_cube[8][3] =
    {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},

        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}};

static GLubyte c_ind[6][4] =
    {
        {0, 2, 6, 4},
        {1, 5, 7, 3},
        {0, 4, 5, 1},
        {2, 3, 7, 6},
        {0, 1, 3, 2},
        {4, 6, 7, 5}};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void circle(float centerX, float centerY, float radius)
{
    glBegin(GL_TRIANGLE_FAN);

    int NUM_SEGMENTS = 24;

    for (int i = 0; i <= NUM_SEGMENTS; i++)
    {
        float angle = 2.0 * 3.1416 * i / NUM_SEGMENTS;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

void cube(float r, float g, float b)
{

    glBegin(GL_QUADS);
    glColor3d(r, g, b);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void cubeWithBorder(float r, float g, float b, int borderIntensity = 50)
{
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();

    glColor3f(((r * 255.0) + borderIntensity) / 255.0, ((g * 255.0) + borderIntensity) / 255.0, ((b * 255.0) + borderIntensity) / 255.0);
    for (GLint i = 0; i < 12; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
        glEnd();
    }
}

void renderBitmapString(float x, float y, void *font, const char *string)
{
    glRasterPos2f(x, y);

    while (*string)
    {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void building(int hasExtension = 0)
{
    // Building
    glPushMatrix();
    glTranslated(0, 0, 10);
    glScaled(70, 30, 20);
    cubeWithBorder(0.5, 0.1, 0.2, 100);
    glPopMatrix();

    if (hasExtension == 1)
    {
        glPushMatrix();
        glTranslated(45, 30, 8);
        glScaled(10, 15, 20);
        cubeWithBorder(0.74, 0.74, 0.74, -100);
        glPopMatrix();

        // Extension top
        glPushMatrix();
        glTranslated(43, 43, 10);
        glScaled(13, 2, 21);
        cubeWithBorder(0.74, 0.74, 0.74, -100);
        glPopMatrix();
    }

    // Rooftop
    glPushMatrix();
    glTranslated(0, 30, 10);
    glScaled(70, 5, 21);
    cubeWithBorder(0.74, 0.74, 0.74, -100);
    glPopMatrix();

    // Base
    glPushMatrix();
    glTranslated(-1, 0, 10);
    glScaled(72, 2, 22);
    cubeWithBorder(0.74, 0.74, 0.74, 20);
    glPopMatrix();

    for (float i = 30.5; i < 30.5 + 9.5; i = i + 0.7)
    {
        glPushMatrix();
        glTranslated(i, 0, 29.5);
        glScaled(0.4, 15, 1);
        cube(0, 0, 0);
        glPopMatrix();
    }

    for (int i = 10; i <= 60; i = i + 10)
    {
        // Line 1
        glPushMatrix();
        glTranslated(i, 0, 31);
        glScaled(0.7, 30, 0);
        cube(0.5, 0.5, 0.5);
        glPopMatrix();
    }

    // Horizontal Line 1
    glPushMatrix();
    glTranslated(0, 15, 31);
    glScaled(70, 3, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();
}

void sideTree()
{

    // Base
    glPushMatrix();
    glTranslated(0, 0, 10);
    glScaled(2, 20, 2);
    cube(139.0 / 255, 121.0 / 255, 94.0 / 255);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, 20, 10);
    glScaled(2, 8, 2);
    cube(139.0 / 255, 121.0 / 255, 94.0 / 255);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, 26, 10);
    glScaled(2, 8, 2);
    cube(139.0 / 255, 121.0 / 255, 94.0 / 255);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, 33, 10);
    glScaled(2.8, 8, 2);
    cube(139.0 / 255, 121.0 / 255, 94.0 / 255);
    glPopMatrix();

    // Leaf
    glPushMatrix();
    glTranslated(0, 33, 10);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(4, 25, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(10, 40, 12);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(3, 25, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-5, 35, 10);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(4.5, 5, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 40, 10);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(3, 25, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-7, 50, 10);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(10, 10, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(12, 32, 10);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(6, 5, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslated(14, 48, 15);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(12, 4, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, 57, 15);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(5, 15, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3, 0, 12);
    glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
    glutSolidSphere(3, 5, 5);
    glPopMatrix();

    for (int i = 0; i < 50; i = i + 2)
    {
        glPushMatrix();
        glTranslated(9, 0, i);
        glScaled(0.3, 5, 0.1);
        cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
        glPopMatrix();
    }

    for (int i = 10; i < 30; i = i + 2)
    {
        glPushMatrix();
        glTranslated(i, 0, 50);
        glScaled(0.3, 5, 0.1);
        cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
        glPopMatrix();
    }
}

void gate()
{
    // Base
    for (int i = -10; i < 35; i++)
    {
        glPushMatrix();
        glTranslated(i, 0, 98);
        glScaled(0.3, 10, 0.1);
        cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(35, 0, 97);
    glScaled(1, 15, 1);
    cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    // HEAD
    glPushMatrix();
    glTranslated(33.2, 15, 97);
    glScaled(15, 2, 1);
    cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (float i = 36.0; i < 46.0; i = i + 0.45)
    {
        glPushMatrix();
        glTranslated(i, 0, 97);
        glScaled(0.1, 10, 0);
        cubeWithBorder(0, 0, 0);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(45.5, 0, 97);
    glScaled(1, 15, 1);
    cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 47; i < 140; i++)
    {
        glPushMatrix();
        glTranslated(i, 0, 98);
        glScaled(0.3, 10, 0.1);
        cubeWithBorder(139.0 / 255, 87.0 / 255, 66.0 / 255);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(40.5, 5.5, 97);
    glColor3f(139.0 / 255, 131.0 / 255, 120.0 / 255);
    circle(0.1, 0.1, 2.0);
    glPopMatrix();
}

void walls()
{
    // left
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(1, 10, 100);
    cube(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 0; i < 100; i += 5)
    {
        // left i
        glPushMatrix();
        glTranslated(0, 0, i);
        glScaled(1.2, 10, 0.1);
        cube(23.0 / 255, 23.0 / 255, 23.0 / 255);
        glPopMatrix();
    }

    // back
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(150, 10, 1);
    cube(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 0; i < 150; i += 5)
    {
        // left i
        glPushMatrix();
        glTranslated(i, 0, 1);
        glScaled(0.1, 10, 1);
        cube(23.0 / 255, 23.0 / 255, 23.0 / 255);
        glPopMatrix();
    }

    // right
    glPushMatrix();
    glTranslated(150, 0, 0);
    glScaled(1, 10, 100);
    cube(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 0; i < 100; i += 5)
    {
        // left i
        glPushMatrix();
        glTranslated(149, 0, i);
        glScaled(1, 10, 0.1);
        cube(23.0 / 255, 23.0 / 255, 23.0 / 255);
        glPopMatrix();
    }
}

void sun(void)
{
    // SUN
    glPushMatrix();

    glColor3f(255.0 / 255.0, 185.0 / 255.0, 15.0 / 255.0);
    glTranslated(36, 97, 2);
    glutSolidSphere(3, 25, 20);
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0);
    glTranslated(35, 100, 0);
    glutSolidSphere(5.2, 25, 20);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++)
    {
        float angle = i * (2.0 * M_PI / 5.2);
        float x1 = 0.0;
        float y1 = 0.0;
        float x2 = 10 * 2 * cos(angle);
        float y2 = 10 * 2 * sin(angle);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    }
    for (int i = 0; i < 6; i++)
    {
        float angle = i * (2.0 * M_PI / 5);
        float x1 = 0.0;
        float y1 = 0.0;
        float x2 = 30 * cos(angle);
        float y2 = 30 * sin(angle);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    }
    glEnd();
}

void pyramid(int frontFace = 20.0)
{
    glBegin(GL_TRIANGLES);

    // Define the vertices of the pyramid
    // Base
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, 1.0);

    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(-1.0, 0.0, 1.0);

    // Front Face
    glVertex3f(0.0, frontFace, 0.0);
    glVertex3f(-1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);

    // Left Face
    glVertex3f(0.0, frontFace, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, 1.0);

    // Right Face
    glVertex3f(0.0, frontFace, 0.0);
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(1.0, 0.0, 1.0);

    glEnd();
}

void trees()
{

    for (int i = 0; i < 100; i += 5)
    {

        glPushMatrix();
        glTranslated(5, 0, i);
        glScaled(0.5, 20, 0.5);
        cube(139.0 / 255, 121.0 / 255, 94.0 / 255);
        glPopMatrix();

        glPushMatrix();
        glTranslated(5.5, 7, i + 0.3);
        glColor3f(0.0 / 255, 139.0 / 255, 69.0 / 255);
        pyramid();
        glPopMatrix();

        glPushMatrix();
        glTranslated(5.5, 10, i + 0.3);
        glColor3f(46.0 / 255, 139.0 / 255, 87.0 / 255);
        pyramid();
        glPopMatrix();

        glPushMatrix();
        glTranslated(5.5, 13, i + 0.3);
        glColor3f(40.0 / 255, 140.0 / 255, 80.0 / 255);
        pyramid();
        glPopMatrix();
    }
}

void minar()
{

    // base
    glPushMatrix();
    glTranslated(0, 0, 16);
    glScaled(25, 2, 7);
    cubeWithBorder(139.0 / 255, 137.0 / 255, 137.0 / 255);
    glPopMatrix();

    // Piller
    glPushMatrix();
    glTranslated(2, 1, 18);
    glScaled(2, 15, 1);
    cubeWithBorder(1.0, 1.0, 1.0, -28);
    glPopMatrix();

    // Middle Piller
    glPushMatrix();
    glTranslated(9.5, 1, 18);
    glScaled(5, 18, 1);
    cubeWithBorder(1.0, 1.0, 1.0, -28);
    glPopMatrix();

    // Right Piller
    glPushMatrix();
    glTranslated(20, 1, 18);
    glScaled(2, 15, 1);
    cubeWithBorder(1.0, 1.0, 1.0, -28);
    glPopMatrix();

    // sun

    glColor3f(1.0, 0.0, 0.0);
    glTranslated(12, 13, 18);
    glutSolidSphere(2.2, 28, 20);
}

void flag()
{
    // base
    glPushMatrix();
    glTranslated(3.25, 0, 38);
    glScaled(5, 1, 4);
    cubeWithBorder(139.0 / 255, 137.0 / 255, 137.0 / 255);
    glPopMatrix();

    // 2nd base
    glPushMatrix();
    glTranslated(4.5, 0, 39);
    glScaled(2.5, 2, 2);
    cubeWithBorder(139.0 / 255, 137.0 / 255, 137.0 / 255);
    glPopMatrix();

    // Stand
    glPushMatrix();
    glTranslated(5.5, 0, 40);
    glScaled(0.5, 20, 0.5);
    cube(0, 0, 0);
    glPopMatrix();

    // Flag
    glPushMatrix();
    glTranslated(6, 16, 40);
    glScaled(5, 3.5, 0);
    cubeWithBorder(46.0 / 255, 139.0 / 255, 87.0 / 255);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8, 17.7, 40.1);
    glColor3f(1.0, 0.0, 0.0);
    circle(0.0, 0.0, 1.1);
    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-3, 3, -3, 3, 2.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
    glViewport(0, 0, width, height);

    // green field
    glPushMatrix();
    // glTranslated(-100,-1,-100);
    glScaled(125, 0, 100);
    cube(162.0 / 255, 205.0 / 255, 90.0 / 255);
    glPopMatrix();

    glPushMatrix();
    glTranslated(125, 0, 60);
    glScaled(25, 0, 40);
    cube(162.0 / 255, 205.0 / 255, 90.0 / 255);
    glPopMatrix();

    // ROAD
    glPushMatrix();
    glTranslated(0, 0, 100);
    glScaled(150, 1, 6);
    cube(112.0 / 255, 128.0 / 255, 144.0 / 255);
    glPopMatrix();

    for (int i = 5; i <= 150; i = i + 5)
    {
        glPushMatrix();
        glTranslated(i, 0, 103.7);
        glScaled(3, 1.5, 0.01);
        cube(1, 1, 1);
        glPopMatrix();
    }

    // SUN
    glPushMatrix();
    sun();
    glPopMatrix();

    // Building
    glPushMatrix();
    glTranslated(10, 0, 0);
    building();
    glPopMatrix();

    // Building 2
    glPushMatrix();
    glTranslated(30, 0, 0);
    building(1);
    glPopMatrix();

    // Building 3
    glPushMatrix();
    glTranslated(115, 0, 15);
    sideTree();
    glPopMatrix();

    // Gate
    glPushMatrix();
    glTranslated(10, 0, 0);
    gate();
    glPopMatrix();

    // Walls
    glPushMatrix();
    glTranslated(0, 0, 0);
    walls();
    glPopMatrix();

    // Trees
    glPushMatrix();
    glTranslated(0, 0, 0);
    trees();
    glPopMatrix();

    // Minar
    glPushMatrix();
    glTranslated(10, 0, 70);
    minar();
    glPopMatrix();

    // Flag
    glPushMatrix();
    glTranslated(47, 0, 5);
    flag();
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'w':
        eyeY = eyeY + 1;
        break;
    case 's':
        eyeY = eyeY - 1;
        break;
    case 'd':
        eyeX = eyeX + 1;
        break;
    case 'a':
        eyeX = eyeX - 1;
        break;

    case 't':
        t = t + 0.1;
        break;

    case 'i':
        lookY = lookY + 1;
        break;
    case 'k':
        lookY = lookY - 1;
        break;
    case 'j':
        lookX = lookX + 1;
        break;
    case 'l':
        lookX = lookX - 1;
        break;

    case '-':
        eyeZ = eyeZ + 1;
        break;
    case '+':
        eyeZ = eyeZ - 1;
        break;
    }

    glutPostRedisplay();
}

void playAudioAsync()
{
    int result = system("aplay music.wav");
}

void stopAudio()
{
    system("pkill aplay");
}

int main(int argc, char **argv)
{
    thread audioThread(playAudioAsync);
    atexit(stopAudio);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 1000);
    glutCreateWindow("High School");
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutMainLoop();
    audioThread.join();

    return 0;
}
