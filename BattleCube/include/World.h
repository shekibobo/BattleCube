#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

#include "Player.h"
#include "Drone.h"
#include <cstdio>

using namespace std;

class Player;
class Drone;

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
        GLfloat FloorPos() { return m_FloorPos; }

        void SetTexture();
        void Draw();

        Player* GetPlayer() {
            //printf("accessing player...\n");
            return m_pPlayer;
        }

        vector<Drone*>& Drones() { return m_pvDrones; }



    protected:
    private:
        GLfloat m_WallLength; //!< Member variable "m_WallLength"
        GLfloat m_FloorPos;
        GLuint m_Texture;
        Player* m_pPlayer;
        Drone* m_pBall;

        vector<Drone*> m_pvDrones;
        vector<Drone*>::iterator it;

};

#endif // WORLD_H
