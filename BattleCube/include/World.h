#ifndef WORLD_H
#define WORLD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>


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

    protected:
    private:
        GLfloat m_WallLength; //!< Member variable "m_WallLength"
        GLuint m_Texture;

};

#endif // WORLD_H
