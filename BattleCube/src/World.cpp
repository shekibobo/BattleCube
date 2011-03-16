#include "../include/World.h"

World::World()
{
    //ctor
    SetTexture();
}

World::~World()
{
    //dtor
}

void World::SetTexture() {
    const char* filename = "../images/gradient.gif";
    int width, height;
    unsigned char *data;
    FILE *file;

    width = 256;
    height = 256;

    // allocate buffer
    data = (unsigned char *) malloc( width * height * 3 );

    // open and read texture data
    file = fopen( filename, "rb");
    fread( data, width * height * 3, 1, file );
    fclose( file );

    //allocate a texture name
    glGenTextures(1, &m_Texture);

    // load the current texture
    glBindTexture( GL_TEXTURE_2D, m_Texture );

    // select modulate to mi texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is large, bilinear filter the original
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // build our texture mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB,
                      GL_UNSIGNED_BYTE, data);

    // free buffer
    free (data);

    glEnable ( GL_TEXTURE_2D );
}

void World::Draw() {
    glBindTexture( GL_TEXTURE_2D, m_Texture );

    glPushMatrix();
        glTranslatef(0.0, 0.0, -World::m_WallLength / 2.0);
        glutSolidCube(World::m_WallLength);
    glPopMatrix();
}
