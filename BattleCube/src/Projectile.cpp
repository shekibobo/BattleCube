#include "../include/Projectile.h"
#include "../include/Drone.h"
#include "../include/World.h"

GLubyte projectileTexture[340][340][3];

Projectile::Projectile(World* world)
{
    //ctor
    setTexture();
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
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    glPushMatrix();
        glColor4fv(m_color);
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 340, 340, 0, GL_RGB, GL_UNSIGNED_BYTE, projectileTexture);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

        glTranslatef(Posx(), Posy(), Posz());
        glRotatef(a, 1.0, 0.0, 0.0);
        glutSolidSphere(Size(), 12, 12);
        glutWireSphere(Size(), 12, 12);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();
}

void Projectile::setTexture() {
    int i, j;
    unsigned char data[3];
    FILE *fp;
    char file[256] = "plasma.dat";
    if((fp = fopen(file, "rb")) == NULL) {
        printf("file not found");
        exit(0);
    }

    for(i = 0; i < 340; i++){
        for(j = 0; j < 340; j++){
            fread(data, sizeof(unsigned char), 3, fp);
            projectileTexture[i][j][0] = (GLubyte) data[0];
            projectileTexture[i][j][1] = (GLubyte) data[1];
            projectileTexture[i][j][2] = (GLubyte) data[2];
        }
    }
}
