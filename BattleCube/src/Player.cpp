#include "../include/Player.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

Player::Player(GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat Boundary)
{
    //ctor
    SetPosX(PosX);
    SetPosY(PosY);
    SetPosZ(PosZ);
    SetBoundary((Boundary / 2.0) - 2.0);
}

Player::~Player()
{
    //dtor
}

void Player::Move() {
    if ( max( fabs(GetDirX()), max ( fabs(GetDirY()), fabs(GetDirZ()) ) ) > 0.0 )
        SetFreefalling(true);

    SetPosX(GetPosX() + GetDirX());
    SetPosY(GetPosY() + GetDirY());
    SetPosZ(GetPosZ() + GetDirZ());

    if (HasReachedBoundary()) { Stop(); }
}

bool Player::HasReachedBoundary() {
    GLfloat boundary = GetBoundary();

    // detect if the player has come into contact with any wall
    GLfloat x = fabs(GetPosX());
    GLfloat y = fabs(GetPosY());
    GLfloat z = fabs(GetPosZ());

    GLfloat maxDist = max(x, max(y, z));

    if (maxDist >= boundary) return true;

    return false;
}
