#include "../include/Wall.h"

Wall::Wall()
{
    //ctor
}

Wall::~Wall()
{
    //dtor
}


void Wall::Draw()
{
    glLoadIdentity();
    glRotatef(Getrotation(), 0.0, 1.0, 0.0);
    glTranslatef(Getposx(), Getposy(), Getposz());

}
