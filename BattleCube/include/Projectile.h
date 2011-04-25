#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

#include "World.h"

#define PI 3.14159265
#define SPEED 3.0

class World;

class Projectile
{
    public:
        /** Default constructor */
        Projectile(World* world);

        Projectile(GLfloat xp, GLfloat yp, GLfloat zp,
             GLfloat xd, GLfloat yd, GLfloat zd,
             GLfloat rc, GLfloat gc, GLfloat bc, GLfloat alpha,
             GLfloat size, World * world)
        {
            SetDir(xd, yd, zd);
            SetPos(xp, yp, zp);
            m_pWorld = world;
            m_size = size;;
            Setcolor(rc, gc, bc, alpha);
        }

        /** Default destructor */
        virtual ~Projectile();
        /** Access m_posx
         * \return The current value of m_posx
         */
        GLfloat Posx() { return m_posx; }
        /** Set m_posx
         * \param val New value to set
         */
        void Setposx(GLfloat val) { m_posx = val; }
        /** Access m_posy
         * \return The current value of m_posy
         */
        GLfloat Posy() { return m_posy; }
        /** Set m_posy
         * \param val New value to set
         */
        void Setposy(GLfloat val) { m_posy = val; }
        /** Access m_posz
         * \return The current value of m_posz
         */
        GLfloat Posz() { return m_posz; }
        /** Set m_posz
         * \param val New value to set
         */
        void Setposz(GLfloat val) { m_posz = val; }
        /** Access m_dirx
         * \return The current value of m_dirx
         */
        GLfloat Dirx() { return m_dirx; }
        /** Set m_dirx
         * \param val New value to set
         */
        void Setdirx(GLfloat val) { m_dirx = val; }
        /** Access m_diry
         * \return The current value of m_diry
         */
        GLfloat Diry() { return m_diry; }
        /** Set m_diry
         * \param val New value to set
         */
        void Setdiry(GLfloat val) { m_diry = val; }
        /** Access m_dirz
         * \return The current value of m_dirz
         */
        GLfloat Dirz() { return m_dirz; }
        /** Set m_dirz
         * \param val New value to set
         */
        void Setdirz(GLfloat val) { m_dirz = val; }
        /** Access m_color[4]
         * \return The current value of m_color[4]
         */
        GLfloat* Color() { return m_color; }
        /** Set m_color[4]
         * \param val New value to set
         */
        void Setcolor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
            m_color[0] = r;
            m_color[1] = g;
            m_color[2] = b;
            m_color[3] = a;
        }

        void SetDir(GLfloat x, GLfloat y, GLfloat z) {
            m_dirx = x; m_diry = y; m_dirz = z;
        }

        void SetPos(GLfloat x, GLfloat y, GLfloat z) {
            m_posx = x; m_posy = y; m_posz = z;
        }

        void setTexture();

        void SetSize(GLfloat val) { m_size = val; }
        GLfloat Size() { return m_size; }

        void Move();
        void Draw();

        World* Env() { return m_pWorld; }

    protected:
    private:
        GLfloat m_posx; //!< Member variable "m_posx"
        GLfloat m_posy; //!< Member variable "m_posy"
        GLfloat m_posz; //!< Member variable "m_posz"
        GLfloat m_dirx; //!< Member variable "m_dirx"
        GLfloat m_diry; //!< Member variable "m_diry"
        GLfloat m_dirz; //!< Member variable "m_dirz"
        GLfloat m_size;
        GLfloat m_color[4]; //!< Member variable "m_color[4]"


        World * m_pWorld;
};

#endif // PROJECTILE_H
