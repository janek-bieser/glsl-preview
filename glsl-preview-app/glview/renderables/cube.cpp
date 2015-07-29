#include "cube.h"

Cube::Cube(GLfloat size) : m_size(size)
{
    setupBuffers();
}

void Cube::render()
{
    glBindVertexArray(m_vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
    glBindVertexArray(0);
}

void Cube::setupBuffers()
{
    GLfloat hs = m_size / 2;

    GLfloat vertices[] = {
        // back
         hs, -hs, -hs, /*normals*/  0,  0, -1, /* texture */ 0, 0,
        -hs, -hs, -hs, /*normals*/  0,  0, -1, /* texture */ 1, 0,
         hs,  hs, -hs, /*normals*/  0,  0, -1, /* texture */ 0, 1,

        -hs, -hs, -hs, /*normals*/  0,  0, -1, /* texture */ 1, 0,
        -hs,  hs, -hs, /*normals*/  0,  0, -1, /* texture */ 1, 1,
         hs,  hs, -hs, /*normals*/  0,  0, -1, /* texture */ 0, 1,

        // front
        -hs, -hs,  hs, /*normals*/  0,  0,  1, /* texture */ 0, 0,
         hs, -hs,  hs, /*normals*/  0,  0,  1, /* texture */ 1, 0,
        -hs,  hs,  hs, /*normals*/  0,  0,  1, /* texture */ 0, 1,

         hs, -hs,  hs, /*normals*/  0,  0,  1, /* texture */ 1, 0,
         hs,  hs,  hs, /*normals*/  0,  0,  1, /* texture */ 1, 1,
        -hs,  hs,  hs, /*normals*/  0,  0,  1, /* texture */ 0, 1,

        // bottom
        -hs, -hs, -hs, /*normals*/  0, -1,  0, /* texture */ 0, 0,
         hs, -hs, -hs, /*normals*/  0, -1,  0, /* texture */ 1, 0,
        -hs, -hs,  hs, /*normals*/  0, -1,  0, /* texture */ 0, 1,

         hs, -hs, -hs, /*normals*/  0, -1,  0, /* texture */ 1, 0,
         hs, -hs,  hs, /*normals*/  0, -1,  0, /* texture */ 1, 1,
        -hs, -hs,  hs, /*normals*/  0, -1,  0, /* texture */ 0, 1,

        // top
        -hs,  hs,  hs, /*normals*/  0,  1,  0, /* texture */ 0, 0,
         hs,  hs,  hs, /*normals*/  0,  1,  0, /* texture */ 1, 0,
        -hs,  hs, -hs, /*normals*/  0,  1,  0, /* texture */ 0, 1,

         hs,  hs,  hs, /*normals*/  0,  1,  0, /* texture */ 1, 0,
         hs,  hs, -hs, /*normals*/  0,  1,  0, /* texture */ 1, 1,
        -hs,  hs, -hs, /*normals*/  0,  1,  0, /* texture */ 0, 1,

        // right
         hs, -hs,  hs, /*normals*/  1,  0,  0, /* texture */ 0, 0,
         hs, -hs, -hs, /*normals*/  1,  0,  0, /* texture */ 1, 0,
         hs,  hs,  hs, /*normals*/  1,  0,  0, /* texture */ 0, 1,

         hs, -hs, -hs, /*normals*/  1,  0,  0, /* texture */ 1, 0,
         hs,  hs, -hs, /*normals*/  1,  0,  0, /* texture */ 1, 1,
         hs,  hs,  hs, /*normals*/  1,  0,  0, /* texture */ 0, 1,

        // left
        -hs, -hs, -hs, /*normals*/ -1,  0,  0, /* texture */ 0, 0,
        -hs, -hs,  hs, /*normals*/ -1,  0,  0, /* texture */ 1, 0,
        -hs,  hs, -hs, /*normals*/ -1,  0,  0, /* texture */ 0, 1,

        -hs, -hs,  hs, /*normals*/ -1,  0,  0, /* texture */ 1, 0,
        -hs,  hs,  hs, /*normals*/ -1,  0,  0, /* texture */ 1, 1,
        -hs,  hs, -hs, /*normals*/ -1,  0,  0, /* texture */ 0, 1

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

