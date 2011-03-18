#include "../include/Drone.h"

Drone::Drone(World * world)
{
    //ctor
    SetDir(((rand() % 200) - 100) / 100.0, 0.0, ((rand() % 200) - 100) / 100.0);
    Setposx(0.0); Setposy(-5.0); Setposz(0.0);
    m_pWorld = world;
    m_size = 20.0;
    Setcolor(1.0, 1.0, 0.3, 0.1);
}

Drone::~Drone()
{
    //dtor
}


void Drone::Move() {
    Setposx(Posx() + Dirx());
    Setposy( Posy() + sin(Diry()) );
    Setposz(Posz() + Dirz());

    GLfloat xbound = Env()->GetWallLength() / 2.0;
    GLfloat lowbound = Env()->FloorPos();

    if (Posx() <= -xbound + Size() || Posx() >= xbound - Size())
        Setdirx(-Dirx());
    if (Posz() <= -xbound + Size() || Posz() >= xbound - Size())
        Setdirz(-Dirz());
    if (Posy() <= lowbound + Size()) Setdiry(Diry() + PI / 8.0);
    Setdiry(Diry() + PI / 45.0);
}


void Drone::Draw() {
    glPushMatrix();
        glColor4fv(m_color);
        glTranslatef(Posx(), Posy(), Posz());
        glutSolidSphere(Size(), 10, 10);
    glPopMatrix();
}
