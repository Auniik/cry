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
// #include<windows.h>
#include <math.h>

using namespace std;

const int width = 1200;
const int height = 1000;
int t = 10;

GLfloat eyeX = 50;
GLfloat eyeY = 40 - 16;
GLfloat eyeZ = 50 + 20 + 15;

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

void building()
{
    // Building
    glPushMatrix();
    glTranslated(0, 0, 10);
    glScaled(70, 30, 20);
    cube(0.5, 0.1, 0.2);
    glPopMatrix();

    // Rooftop
    glPushMatrix();
    glTranslated(0, 30, 10);
    glScaled(70, 1, 22);
    cube(0.74, 0.74, 0.74);
    glPopMatrix();

    // Base
    glPushMatrix();
    glTranslated(0, 0, 10);
    glScaled(70, 2, 22);
    cube(0.74, 0.74, 0.74);
    glPopMatrix();

    // Gate
    glPushMatrix();
    glTranslated(30, 0, 30);
    glScaled(10, 15, 1);
    cube(0.33, 0.33, 0.33);
    glPopMatrix();

    // Gate separator
    glPushMatrix();
    glTranslated(35, 1, 32);
    glScaled(0.3, 13, 0);
    cube(0.7, 0.7, 0.7);
    glPopMatrix();

    // Line 1
    glPushMatrix();
    glTranslated(10, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Line 2
    glPushMatrix();
    glTranslated(20, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Line 3
    glPushMatrix();
    glTranslated(30, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Line 4
    glPushMatrix();
    glTranslated(40, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Line 5
    glPushMatrix();
    glTranslated(50, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Line 6
    glPushMatrix();
    glTranslated(60, 0, 31);
    glScaled(0.7, 30, 0);
    cube(0.5, 0.5, 0.5);
    glPopMatrix();

    // Horizontal Line 1
    glPushMatrix();
    glTranslated(0, 15, 31);
    glScaled(70, 3, 0);
    cube(0.5, 0.5, 0.5);
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
    glScaled(120, 10, 1);
    cube(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 0; i < 120; i += 5)
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
    glTranslated(120, 0, 0);
    glScaled(1, 10, 120);
    cube(139.0 / 255, 87.0 / 255, 66.0 / 255);
    glPopMatrix();

    for (int i = 0; i < 120; i += 5)
    {
        // left i
        glPushMatrix();
        glTranslated(119.9, 0, i);
        glScaled(1, 10, 0.1);
        cube(23.0 / 255, 23.0 / 255, 23.0 / 255);
        glPopMatrix();
    }
}

void sun(void)
{
    glColor3f(1.0, 1.0, 0.0);
    glTranslated(35, 70, 0);
    glutSolidSphere(5.2, 25, 20);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++)
    {
        float angle = i * (2.0 * M_PI / 5.2);
        float x1 = 0.0;
        float y1 = 0.0;
        float x2 = 10 * cos(angle);
        float y2 = 10 * sin(angle);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    }
    glEnd();
}

void pyramid()
{
    glBegin(GL_TRIANGLES);

    // Define the vertices of the pyramid
    // Base
    glVertex3f(-1.0, 0.0, -1.0); // Vertex 1
    glVertex3f(1.0, 0.0, -1.0);  // Vertex 2
    glVertex3f(1.0, 0.0, 1.0);   // Vertex 3

    glVertex3f(-1.0, 0.0, -1.0); // Vertex 1
    glVertex3f(1.0, 0.0, 1.0);   // Vertex 3
    glVertex3f(-1.0, 0.0, 1.0);  // Vertex 4

    // Front Face
    glVertex3f(0.0, 20.0, 0.0); // Vertex 5
    glVertex3f(-1.0, 0.0, 1.0); // Vertex 4
    glVertex3f(1.0, 0.0, 1.0);  // Vertex 3

    // Left Face
    glVertex3f(0.0, 20.0, 0.0);  // Vertex 5
    glVertex3f(-1.0, 0.0, -1.0); // Vertex 1
    glVertex3f(-1.0, 0.0, 1.0);  // Vertex 4

    // Right Face
    glVertex3f(0.0, 20.0, 0.0); // Vertex 5
    glVertex3f(1.0, 0.0, -1.0); // Vertex 2
    glVertex3f(1.0, 0.0, 1.0);  // Vertex 3

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
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
    glViewport(0, 0, width, height);

    // green field
    glPushMatrix();
    // glTranslated(-100,-1,-100);
    glScaled(120, 0, 100);
    cube(162.0 / 255, 205.0 / 255, 90.0 / 255);
    glPopMatrix();

    // SUN
    glPushMatrix();
    sun();
    glPopMatrix();

    // Building
    glPushMatrix();
    glTranslated(10, 0, 0);
    building();
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

    // Trees
    glPushMatrix();
    glTranslated(80, 0, 0);
    minar();
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

    case '+':
        eyeZ = eyeZ + 1;
        break;
    case '-':
        eyeZ = eyeZ - 1;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
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

    return 0;
}
