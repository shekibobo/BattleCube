/*
 * BattleCube
 *
 * Written by Joshua Kovach March 2011
 *
 * A first person shooter in a 3d environment.
 *
 * You move around inside the Battle Cube with bouncing drones.
 * Press SPACE to shoot a bullet.  Bullets will bounc around the room.
 * Press '+' to spawn more drones.
 * Move forward or backward by pressing 'w' or 's' respectively.
 * Look left and right by pressing 'a' and 'd' respectively.
 * Objects can detect collisions with walls and each other and will react accordingly.
 *
 * Press ESC to quit.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "include/Player.h"
#include "include/World.h"
#include <stdlib.h>

World world = World();

bool keyStates[256];

/* set up lighting and textures */
GLfloat wallpos = world.GetPlayer()->GetBoundary();
const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat light_position0[] = { 0.0, 20.0, 0.0, 0.0 };
const GLfloat light_position1[] = { 0.0, 20, 0.0, 0.0f };
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
    light_position0[0] = world.GetPlayer()->GetPosX();
    light_position0[1] = world.GetPlayer()->GetPosY();
    light_position0[2] = world.GetPlayer()->GetPosZ();
    light_position0[3] = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    world.GetPlayer()->Move(keyStates);
    world.GetPlayer()->Draw();
    world.Draw();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
            exit(0);
            break;

        case '+':
            world.NewDrones();
            break;
        case ' ':
            world.NewBullet();
            break;
        case 't':
            world.GetPlayer()->SetFirstPerson(true);
            break;
        case 'y':
            world.GetPlayer()->SetFirstPerson(false);
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
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

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
