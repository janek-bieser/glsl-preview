#ifndef CUBE_H
#define CUBE_H

#include <qopengl.h>
#include "renderable.h"

/*!
 * \brief A Cube Renderable
 */
class Cube : public Renderable
{
public:
    /*!
     * \brief Create a cube of a certain size.
     * \param size
     */
    Cube(GLfloat size);

    void render() override;

private:
    GLfloat m_size;
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;

    void setupBuffers();
};

#endif // CUBE_H
