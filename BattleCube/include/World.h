#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Player.h"
#include <cstdio>

class Player;

class World
{
    public:
        /** Default constructor */
        World();
        /** Default destructor */
        virtual ~World();

        /** access m_WallLength */
        GLfloat GetWallLength() { return m_WallLength; }
        void SetWallLength(GLfloat val) { m_WallLength = val; }

        void SetTexture();
        void Draw();


        Player* GetPlayer() {
            //printf("accessing player...\n");
            return m_pPlayer;
        }

    protected:
    private:
        GLfloat m_WallLength; //!< Member variable "m_WallLength"
        GLuint m_Texture;
        Player* m_pPlayer;

};

#endif // WORLD_H
