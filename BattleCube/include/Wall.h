#ifndef WALL_H
#define WALL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#include "World.h"

#define PI 3.14159265

class World;
class Wall
{
    public:
        /** Default constructor */
        Wall();
        /** Default destructor */
        virtual ~Wall();
        /** Access m_height
         * \return The current value of m_height
         */
        GLfloat Getheight() { return m_height; }
        /** Set m_height
         * \param val New value to set
         */
        void Setheight(GLfloat val) { m_height = val; }
        /** Access m_posx
         * \return The current value of m_posx
         */
        GLfloat Getposx() { return m_posx; }
        /** Set m_posx
         * \param val New value to set
         */
        void Setposx(GLfloat val) { m_posx = val; }
        /** Access m_posy
         * \return The current value of m_posy
         */
        GLfloat Getposy() { return m_posy; }
        /** Set m_posy
         * \param val New value to set
         */
        void Setposy(GLfloat val) { m_posy = val; }
        /** Access m_posz
         * \return The current value of m_posz
         */
        GLfloat Getposz() { return m_posz; }
        /** Set m_posz
         * \param val New value to set
         */
        void Setposz(GLfloat val) { m_posz = val; }
        /** Access m_depth
         * \return The current value of m_depth
         */
        GLfloat Getdepth() { return m_depth; }
        /** Set m_depth
         * \param val New value to set
         */
        void Setdepth(GLfloat val) { m_depth = val; }

        void Setrotation(GLfloat val) { m_rotation = val; }
        GLfloat Getrotation() { return m_rotation; }

        void Draw();
    protected:
    private:
        GLfloat m_height; //!< Member variable "m_height"
        GLfloat m_posx; //!< Member variable "m_posx"
        GLfloat m_posy; //!< Member variable "m_posy"
        GLfloat m_posz; //!< Member variable "m_posz"
        GLfloat m_depth; //!< Member variable "m_depth"
        GLfloat m_rotation;
};

#endif // WALL_H
