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

    SetFirstPerson(true);
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

    if (keyStates['a'] && inBounds(false) ) {
        SetPosZ(GetPosZ() - GetDirX());
        SetPosX(GetPosX() + GetDirZ());
    }

    if (keyStates['d'] && inBounds(false) ) {
        SetPosZ(GetPosZ() + GetDirX());
        SetPosX(GetPosX() - GetDirZ());
    }

    if (keyStates['a']) {

    }

    if (keyStates['d']) {


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

    if (FirstPerson()) {
        gluLookAt(GetPosX(), GetPosY(), GetPosZ(),
                  GetLookX(), GetLookY(), GetLookZ(),
                  0.0, 1.0, 0.0);
    } else {
        gluLookAt(sin(LookAngle()) - GetPosX(), GetPosY(), cos(LookAngle()) - GetPosZ(),
                  GetLookX(), GetLookY(), GetLookZ(),
                  0.0, 1.0, 0.0);
        glPushMatrix();
            glColor3f(1.0, 0.5, 0.1);
            glTranslatef(GetPosX(), GetPosY(), GetPosZ());
            glutSolidCube(8.0);
        glPopMatrix();
    }
}

World Player::Env()  { return *m_pWorld; }
