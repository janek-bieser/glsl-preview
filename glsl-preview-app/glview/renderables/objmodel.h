#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QString>
#include <qopengl.h>
#include "renderable.h"
#include "../obj_loader.h"

class OBJModel : public Renderable
{
public:
    OBJModel(const QString& path);
    ~OBJModel();

    void render() override;

private:
    void createBuffers(mesh_t* mesh);

    GLuint m_vertexArray;
    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;

    //GLuint m_vertexCount;
    GLuint m_elementCount;
};

#endif // OBJMODEL_H
