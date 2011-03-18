#include "../include/Drone.h"


Drone::Drone(World* world) {
    //ctor
    SetDir(((rand() % 200) - 100) / 100.0, 0.0, ((rand() % 200) - 100) / 100.0);
    Setposx(0.0); Setposy(-5.0); Setposz(0.0);
    m_pWorld = world;
    m_size = 6.0;
    Setcolor(1.0, 0.0, 0.3, 0.5);
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
    if (Posy() <= lowbound + Size()) Setdiry((Diry() + PI / 8.0));

    Setdiry(Diry() + PI / 20.0);
}


void Drone::Draw() {
    static int slices = 16;
    static int stacks = 16;
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glColor4fv(m_color);
    glPushMatrix();
        glTranslatef(Posx(), Posy(), Posz());
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(Size(),slices,stacks);
    glPopMatrix();

}
