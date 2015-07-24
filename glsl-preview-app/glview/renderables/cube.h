#ifndef CUBE_H
#define CUBE_H

#include <qopengl.h>
#include "renderable.h"

class Cube : public Renderable
{
public:
    Cube(GLfloat size);

    void render();

private:
    GLfloat m_size;
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;

    void setupBuffers();
};

#endif // CUBE_H
