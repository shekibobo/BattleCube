#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


class Player
{
    public:
        /** Default constructor */
        Player(GLfloat PosX, GLfloat PosY, GLfloat PosZ, GLfloat Boundary);
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

        GLfloat GetLookX() { return m_LookX; }
        void SetLookX(GLfloat val) { m_LookX = val; }

        GLfloat GetLookY() { return m_LookY; }
        void SetLookY(GLfloat val) { m_LookY = val; }

        GLfloat GetLookZ() { return m_LookZ; }
        void SetLookZ(GLfloat val) { m_LookZ = val; }

        /** Set or Determine if Freefall is active */
        bool IsFreefalling() { return isFreefalling; }
        void SetFreefalling(bool val) { isFreefalling = val; }

        /** Set and Get movement limits */
        void SetBoundary(GLfloat val) { m_Boundary = val; }
        GLfloat GetBoundary() { return m_Boundary; }

        void Look(GLfloat x, GLfloat y, GLfloat z);

        /** Movement methods */
        void Move();
        void Stop() {
            //bounce
            SetDirX(GetDirX() * -1.0);
            SetDirY(GetDirY() * -1.0);
            SetDirZ(GetDirZ() * -1.0);
            Move();
            //stop
            SetFreefalling(false);
            SetDirX(0.0);
            SetDirY(0.0);
            SetDirZ(0.0);
        }
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

        GLfloat m_Boundary;
        bool isFreefalling; //!< Member variable "isFreefalling?"

        bool HasReachedBoundary();
};

#endif // PLAYER_H
