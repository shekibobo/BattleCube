#include "../include/Player.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define PI 3.14159265

using namespace std;

Player::Player(GLfloat PosX, GLfloat PosY, GLfloat PosZ, World *world)
{
    m_pWorld = world;

    //ctor
    SetPosX(PosX);
    SetPosY(PosY);
    SetPosZ(PosZ);

    SetLookAngle(PI);
    SetDir(1.0, 0.0, -1.0);
    SetBoundary((Env().GetWallLength() / 2.0) - 2.0);
    printf("Boundary: %f\n", GetBoundary());


}

Player::~Player()
{
    //dtor
}

void Player::Move(bool keyStates[]) {
    if ( inBounds(true) && keyStates['w']) {
        SetPosZ(GetPosZ() + GetDirZ());
        SetPosX(GetPosX() + GetDirX());
    }
    if ( inBounds(false) && keyStates['s']) {
        SetPosZ(GetPosZ() - GetDirZ());
        SetPosX(GetPosX() - GetDirX());
    }

    if (keyStates['a']) {
        SetLookAngle(LookAngle() + PI / 45.0);
        SetDir( sin(LookAngle()), 0.0, cos(LookAngle()) );
    }
    if (keyStates['d']) {
        SetLookAngle(LookAngle() - PI / 45.0);
        SetDir(sin(LookAngle()), 0.0, cos(LookAngle()) );

    }
}


bool Player::inBounds(bool forward) {
    if (forward) {
        if (GetDirX() > 0 && GetPosX() >= GetBoundary() - 2) return false;
        if (GetDirZ() > 0 && GetPosZ() >= GetBoundary() - 2) return false;
        if (GetDirX() < 0 && GetPosX() <= -GetBoundary() + 2) return false;
        if (GetDirZ() < 0 && GetPosZ() <= -GetBoundary() + 2) return false;

        return true;
    } else {
        if (GetDirX() < 0 && GetPosX() >= GetBoundary() - 2) return false;
        if (GetDirZ() < 0 && GetPosZ() >= GetBoundary() - 2) return false;
        if (GetDirX() > 0 && GetPosX() <= -GetBoundary() + 2) return false;
        if (GetDirZ() > 0 && GetPosZ() <= -GetBoundary() + 2) return false;

        return true;
    }
}

void Player::Draw() {
    /*
    gluLookAt(GetPosX(), GetPosY(), GetPosZ(),
              GetPosX(), GetPosY(), GetPosZ() - 1.0,
              0.0, 1.0, 0.0);
              */
    Look();

}

void Player::Look() {
    SetLookX(sin(LookAngle()) + GetPosX());
    SetLookZ(cos(LookAngle()) + GetPosZ());

    gluLookAt(GetPosX(), GetPosY(), GetPosZ(),
              GetLookX(), GetLookY(), GetLookZ(),
              0.0, 1.0, 0.0);



}

World Player::Env()  { return *m_pWorld; }
