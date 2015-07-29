#ifndef QUAD_H
#define QUAD_H

#include <qopengl.h>
#include "renderable.h"

class Quad : public Renderable
{
public:
    Quad(GLfloat width, GLfloat height);

    void render() override;

private:
    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
    GLfloat m_width;
    GLfloat m_height;

private:
    void setupBuffers();
};

#endif // QUAD_H
