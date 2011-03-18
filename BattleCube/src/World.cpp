#include "../include/World.h"

using namespace std;

World::World()
{
    //ctor
    SetTexture();
    SetWallLength(400);
    m_FloorPos = -20.0;

    printf("creating player...\n");
    m_pPlayer = new Player(0.0, 0.0, 0.0, this);
    printf("player created.\n");

    for (int i = 1; i <= 5; i++) Drones().push_back(new Drone(this));
}

World::~World()
{
    //dtor
}

void World::SetTexture() {

}

void World::NewDrones() {
    Drones().push_back(new Drone(this));
}

void World::NewBullet() {
    Bullets().push_back(new Projectile(this));
}

void World::Draw() {

    glColor3f(0.0, 0.0, 0.0);
    GLfloat size = World::m_WallLength;
    GLfloat pos = size / 2.0;

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
        glTranslatef(0.0, FloorPos(), 0.0);
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


    for (it = Drones().begin(); it != Drones().end(); it++) {
        (*it)->Move();
        (*it)->Draw();

    }

    for (bit = Bullets().begin(); bit != Bullets().end(); bit++) {
        (*bit)->Move();
        (*bit)->Draw();
        for (it = Drones().begin(); it != Drones().end(); it++) {
            if ( distance_squared((*it)->Posx(), (*bit)->Posx(), (*it)->Posz(), (*bit)->Posz()) <= ( (*it)->Size() + (*bit)->Size() ) ) {
                Bullets().erase(bit);
                Drones().erase(it);
            }
        }
    }
}
