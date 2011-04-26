#include "../include/Drone.h"

#define GRAVITY 0.05

GLubyte droneTexture[340][340][3];

Drone::Drone(World* world) {
    //ctor
    setTexture();
    SetDir(((rand() % 200) - 100) / 100.0, 0.0, ((rand() % 200) - 100) / 100.0);
    Setposx(0.0); Setposy(0.0); Setposz(0.0);
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
    Setposy(Posy() + Diry());
    Setposz(Posz() + Dirz());

    GLfloat xbound = Env()->GetWallLength() / 2.0;
    GLfloat lowbound = Env()->FloorPos();

    if (Posx() <= -xbound + Size() || Posx() >= xbound - Size())
        Setdirx(-Dirx());
    if (Posz() <= -xbound + Size() || Posz() >= xbound - Size())
        Setdirz(-Dirz());
    if (Posy() <= lowbound + Size()) {
        Setposy(lowbound + Size());
        Setdiry(-Diry() + GRAVITY); // add one so it doesn't lose its bounce
    }

    Setdiry(Diry() - GRAVITY);
}


void Drone::Draw() {
    static int slices = 16;
    static int stacks = 16;
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glColor4fv(m_color);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 340, 340, 0, GL_RGB, GL_UNSIGNED_BYTE, droneTexture);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);

            glTranslatef(Posx(), Posy(), Posz());
            glRotatef(atan2f(Dirx(), Dirz()),0,1,0);
            glRotated(90,1,0,0);
            glutSolidSphere(Size(),slices,stacks);
            glColor3f(0.0, 0.0, 0.0);
            glutWireSphere(Size(), slices, stacks);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);

        glPushMatrix();
            glTranslatef(5.0, 0.0, 0.0);
            glRotatef(a,1,0,0);
            glutSolidCube(3.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-5.0, 0.0, 0.0);
            glRotatef(-a,1,0,0);
            glutSolidCube(3.0);
        glPopMatrix();

    glPopMatrix();

}

void Drone::setTexture() {
    int i, j;
    unsigned char data[3];
    FILE *fp;
    char file[256] = "smiley.dat";
    if((fp = fopen(file, "rb")) == NULL) {
        printf("file not found");
        exit(0);
    }

    for(i = 0; i < 340; i++){
        for(j = 0; j < 340; j++){
            fread(data, sizeof(unsigned char), 3, fp);
            droneTexture[i][j][0] = (GLubyte) data[0];
            droneTexture[i][j][1] = (GLubyte) data[1];
            droneTexture[i][j][2] = (GLubyte) data[2];
        }
    }
}
