#include "quad.h"

Quad::Quad(GLfloat width, GLfloat height) : m_width(width), m_height(height)
{
    setupBuffers();
}

void Quad::render()
{
    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void Quad::setupBuffers()
{
    GLfloat hw = m_width / 2;
    GLfloat hh = m_height / 2;

    GLfloat vertices[] = {
        -hw, -hh, 0, /* normals */ 0, 0, 1, /* texture */ 0, 0,
         hw, -hh, 0, /* normals */ 0, 0, 1, /* texture */ 1, 0,
         hw,  hh, 0, /* normals */ 0, 0, 1, /* texture */ 1, 1,
        -hw,  hh, 0, /* normals */ 0, 0, 1, /* texture */ 0, 1
    };

    #define STRIDE 8

    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);

    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * STRIDE, NULL);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * STRIDE, (GLvoid*)(sizeof(GLfloat) * 3));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * STRIDE, (GLvoid*)(sizeof(GLfloat) * 6));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

