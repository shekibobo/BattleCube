#include "../include/World.h"

using namespace std;
GLubyte wallTexture[340][340][3];
GLubyte groundTexture[340][340][3];

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

void World::NewDrones() {
    Drones().push_back(new Drone(this));
}

void World::NewBullet() {
    Bullets().push_back(new Projectile(this));
}

void World::SetTexture(){
    int i, j;
    unsigned char data[3];
    FILE *fp;
    char file[256] = "wall.dat";
    char file2[256] = "ground.dat";
    if((fp = fopen(file, "rb")) == NULL) {
        printf("file not found");
        exit(0);
    }

    for(i = 0; i < 340; i++){
        for(j = 0; j < 340; j++){
            fread(data, sizeof(unsigned char), 3, fp);
            wallTexture[i][j][0] = (GLubyte) data[0];
            wallTexture[i][j][1] = (GLubyte) data[1];
            wallTexture[i][j][2] = (GLubyte) data[2];
        }
    }

    if((fp = fopen(file2, "rb")) == NULL) {
        printf("file not found");
        exit(0);
    }
    for(i = 0; i < 340; i++){
        for(j = 0; j < 340; j++){
            fread(data, sizeof(unsigned char), 3, fp);
            groundTexture[i][j][0] = (GLubyte) data[0];
            groundTexture[i][j][1] = (GLubyte) data[1];
            groundTexture[i][j][2] = (GLubyte) data[2];
        }
    }
}

void World::Draw() {

    bool collision = false;

    GLfloat size = World::m_WallLength;
    GLfloat pos = size / 2.0;

    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 340, 340, 0, GL_RGB, GL_UNSIGNED_BYTE, groundTexture);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 5.0); glVertex3f(-pos, FloorPos(), pos);
            glTexCoord2f(5.0, 5.0); glVertex3f(pos, FloorPos(), pos);
            glTexCoord2f(5.0, 0.0); glVertex3f(pos, FloorPos(), -pos);
            glTexCoord2f(0.0, 0.0); glVertex3f(-pos, FloorPos(), -pos);

            glTexCoord2f(0.0, 0.0); glVertex3f(-pos, 50, -pos);
            glTexCoord2f(5.0, 0.0); glVertex3f(pos, 50, -pos);
            glTexCoord2f(5.0, 5.0); glVertex3f(pos, 50, pos);
            glTexCoord2f(0.0, 5.0); glVertex3f(-pos, 50, pos);

        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 340, 340, 0, GL_RGB, GL_UNSIGNED_BYTE, wallTexture);
        glBegin(GL_QUADS);


    glPushMatrix();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 340, 340, 0, GL_RGB, GL_UNSIGNED_BYTE, wallTexture);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_POLYGON);
            //wall1
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-pos, FloorPos(), -pos);
            glTexCoord2f(5.0, 1.0);
            glVertex3f(pos, FloorPos(), -pos);
            glTexCoord2f(5.0, 0.0);
            glVertex3f(pos, 50, -pos);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-pos, 50, -pos);

            //wall2
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-pos, 50, pos);
            glTexCoord2f(5.0, 0.0);
            glVertex3f(pos, 50, pos);
            glTexCoord2f(5.0, 1.0);
            glVertex3f(pos, FloorPos(), pos);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-pos, FloorPos(), pos);

            //wall3
            glTexCoord2f(0.0, 1.0);
            glVertex3f(pos, FloorPos(), -pos);
            glTexCoord2f(5.0, 1.0);
            glVertex3f(pos, FloorPos(), pos);
            glTexCoord2f(5.0, 0.0);
            glVertex3f(pos, 50, pos);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(pos, 50, -pos);

            //wall4
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-pos, 50, -pos);
            glTexCoord2f(5.0, 0.0);
            glVertex3f(-pos, 50, pos);
            glTexCoord2f(5.0, 1.0);
            glVertex3f(-pos, FloorPos(), pos);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-pos, FloorPos(), -pos);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    for (it = Drones().begin(); it != Drones().end(); it++) {
        (*it)->Move();
        (*it)->Draw();
    }

    bit = Bullets().begin();
    while ( bit != Bullets().end() ) {
        (*bit)->Move();
        (*bit)->Draw();
        if ((*bit)->Size() > 50) bit = Bullets().erase(bit);
        else ++bit;
    }

    it = Drones().begin();
    while( it != Drones().end() )
    {
        collision = false;
        bit = Bullets().begin();
        while ( bit != Bullets().end() ) {
            if ( distance_squared((*it)->Posx(), (*it)->Posz(), (*bit)->Posx(), (*bit)->Posz()) <= pow((*it)->Size() + (*bit)->Size(), 2) ) {
                (*bit)->Stop();
                it = Drones().erase(it);
                collision = true;
                break;
            }
            else
            {
                ++bit;
            }
        }
        if (!collision) ++it;

    }
}
