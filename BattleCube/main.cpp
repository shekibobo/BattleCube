/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "include/Player.h"
#include "include/World.h"
#include <stdlib.h>

#define ROOM_LENGTH 500

static int slices = 16;
static int stacks = 16;
Player player = Player(0.0, 0.0, 5.0, ROOM_LENGTH);
World world = World();
bool keyStates[256];

/* set up lighting and textures */
GLfloat wallpos = ROOM_LENGTH / 2.0;
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.5f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat light_position0[] = { wallpos, 0.0, wallpos, 0.0f };
const GLfloat light_position1[] = { -wallpos, 0.0, -wallpos, 0.0f };
const GLfloat light_position2[] = { -wallpos, 0.0, wallpos, 0.0f };
const GLfloat light_position3[] = { wallpos, 0.0, -wallpos, 0.0f };



const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 10.0f };

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 800.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    light_position0[0] = player.GetPosX();
    light_position0[1] = player.GetPosY();
    light_position0[2] = player.GetPosZ();
    light_position0[3] = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    world.Draw();
    player.Move();
    gluLookAt(player.GetPosX(), player.GetPosY(), player.GetPosZ(),
              player.GetPosX(), player.GetPosY(), player.GetPosZ() - 1.0,
              0.0, 1.0, 0.0);

    glPushMatrix();
        glColor3f(0.0, 1.0, 1.0);
        glScalef(-1.0, -1.0, -1.0);
        glutSolidCube(ROOM_LENGTH);
        glutWireCube(ROOM_LENGTH);
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
        case 'w':
            if (!player.IsFreefalling())
                player.SetDirZ(-1.0);
            break;
        case 's':
            if (!player.IsFreefalling())
                player.SetDirZ(1.0);
            break;
        case 'a':
            if (!player.IsFreefalling())
                player.SetDirX(-1.0);
            break;
        case 'd':
            if (!player.IsFreefalling())
                player.SetDirX(1.0);
            break;
        default:
            keyStates[key] = true;
            break;
    }
    glutPostRedisplay();
}

static void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

static void idle(void)
{
    glutPostRedisplay();
}

void init()
{

}



/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,450);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIgnoreKeyRepeat(1);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

    glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}
