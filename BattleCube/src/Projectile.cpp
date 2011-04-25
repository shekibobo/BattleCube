#include "../include/Projectile.h"
#include "../include/Drone.h"

Projectile::Projectile(World* world)
{
    //ctor
    m_pWorld = world;
    Player* player = Env()->GetPlayer();
    SetPos(player->GetPosX(),
           player->GetPosY(),
           player->GetPosZ());
    SetDir(player->GetLookX() - Posx(),
           player->GetLookY() - Posy(),
           player->GetLookZ() - Posz());

    m_size = 2.0;
    Setcolor(1.0, 0.0, 0.0, 1.0);
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::Move() {
    Setposx(Posx() + Dirx() * SPEED);
    Setposy(Posy() + Diry() * SPEED);
    Setposz(Posz() + Dirz() * SPEED);

    GLfloat xbound = Env()->GetWallLength() / 2.0;

    if (Posx() <= -xbound + Size() || Posx() >= xbound - Size()) {
        Setdirx(0); //Setdirx(-Dirx());
        Setdirz(0);
    }
    if (Posz() <= -xbound + Size() || Posz() >= xbound - Size()) {
        Setdirx(0); //Setdirx(-Dirx());
        Setdirz(0);
    }
    if (Dirx() == 0 && Dirz() == 0) {
        SetSize(Size() + 2);
    }
}

void Projectile::Draw() {
    glPushMatrix();
        glColor4fv(m_color);
        glTranslatef(Posx(), Posy(), Posz());
        glutSolidSphere(Size(), 6, 6);
    glPopMatrix();
}
