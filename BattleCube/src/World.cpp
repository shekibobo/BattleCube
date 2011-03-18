#include "../include/World.h"

using namespace std;

World::World()
{
    //ctor
    SetTexture();
    SetWallLength(400);

    printf("creating player...\n");
    m_pPlayer = new Player(0.0, 0.0, 0.0, this);
    printf("player created.\n");
}

World::~World()
{
    //dtor
}

void World::SetTexture() {

}

void World::Draw() {
    static int slices = 16;
    static int stacks = 16;
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glColor3f(0.0, 0.0, 0.0);
    GLfloat size = World::m_WallLength;
    GLfloat pos = size / 2.0;

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

    glColor3f(0.1, 0.1, 0.1);
    glPushMatrix();
        glTranslatef(0.0, 0.0, -pos);
        glScalef(1.0, 0.5, 0.001);
        glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 0.0, pos);
        glScalef(1.0, 0.5, 0.001);
        glutSolidCube(size);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, -20.0, 0.0);
        glScalef(1.0, 0.001, 1.0);
        glutSolidCube(size);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(pos, 0.0, 0.0);
        glScalef(0.001, 0.5, 1.0);
        glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-pos, 0.0, 0.0);
        glScalef(0.001, 0.5, 1.0);
        glutSolidCube(size);
    glPopMatrix();
}
