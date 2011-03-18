#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../include/World.h"

class World;

class Player
{
    public:
        /** Default constructor */
        Player(GLfloat PosX, GLfloat PosY, GLfloat PosZ, World *world);
        /** Default destructor */
        virtual ~Player();

        /** Set and Get Life Count */
        unsigned int GetLife() { return m_Life; }
        void SetLife(unsigned int val) { m_Life = val; }

        /** Set and Get Position on the x-axis */
        GLfloat GetPosX() { return m_PosX; }
        void SetPosX(GLfloat val) { m_PosX = val; }

        /** Set and Get Position on the y-axis */
        GLfloat GetPosY() { return m_PosY; }
        void SetPosY(GLfloat val) { m_PosY = val; }

        /** Set and Get Position on the z-axis */
        GLfloat GetPosZ() { return m_PosZ; }
        void SetPosZ(GLfloat val) { m_PosZ = val; }

        /** Set and Get Direction on the x-axis */
        GLfloat GetDirX() { return m_DirX; }
        void SetDirX(GLfloat val) { m_DirX = val; }

        /** Set and Get Direction on the y-axis */
        GLfloat GetDirY() { return m_DirY; }
        void SetDirY(GLfloat val) { m_DirY = val; }

        /** Set and Get Direction on the z-axis */
        GLfloat GetDirZ() { return m_DirZ; }
        void SetDirZ(GLfloat val) { m_DirZ = val; }

        void SetDir(GLfloat x, GLfloat y, GLfloat z) {
            m_DirX = x;
            m_DirY = y;
            m_DirZ = z;
        }

        GLfloat GetLookX() { return m_LookX; }
        void SetLookX(GLfloat val) { m_LookX = val; }

        GLfloat GetLookY() { return m_LookY; }
        void SetLookY(GLfloat val) { m_LookY = val; }

        GLfloat GetLookZ() { return m_LookZ; }
        void SetLookZ(GLfloat val) { m_LookZ = val; }

        void SetLook(GLfloat x, GLfloat y, GLfloat z) {
            m_LookX = x;
            m_LookY = y;
            m_LookZ = z;
        }

        /** Set and Get movement limits */
        void SetBoundary(GLfloat val) { m_Boundary = val; }
        GLfloat GetBoundary() { return m_Boundary; }

        void Look();
        GLfloat LookAngle() { return m_LookAngle; }
        GLfloat SetLookAngle(GLfloat val) { m_LookAngle = val; }

        /** Movement methods */
        void Move(bool keyStates[]);

        void Draw();
        World Env();

        bool inBounds(bool);

        bool SetFirstPerson(bool val) { m_FirstPerson = val; }
        bool FirstPerson() { return m_FirstPerson; }

    protected:
    private:
        unsigned int m_Life; //!< Member variable "m_Life"
        GLfloat m_PosX; //!< Member variable "m_posX"
        GLfloat m_PosY; //!< Member variable "m_posY"
        GLfloat m_PosZ; //!< Member variable "m_posZ"

        GLfloat m_DirX; //!< Member variable "m_dirX"
        GLfloat m_DirY; //!< Member variable "m_dirY"
        GLfloat m_DirZ; //!< Member variable "m_dirZ"

        GLfloat m_LookX;
        GLfloat m_LookY;
        GLfloat m_LookZ;

        GLfloat m_LookAngle;

        GLfloat m_Boundary;

        bool m_FirstPerson;

        World *m_pWorld;
};

#endif // PLAYER_H
