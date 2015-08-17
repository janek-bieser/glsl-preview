#include "objmodel.h"
#include <qdebug.h>

OBJModel::OBJModel(const QString& path)
{
    const std::string tmpPath = path.toStdString();
    const char* c_path = tmpPath.c_str();

    mesh_loader_result_t result = NewMeshFromOBJFile(c_path);

    if (result.status == MESH_LOADER_SUCCESS) {
        qDebug() << "Loaded Mesh!";
        createBuffers(&result.mesh);
    } else {
        qDebug() << "Error loading mesh:" << result.status;
    }

    DeleteMesh(&result.mesh);
}

OBJModel::~OBJModel()
{
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void OBJModel::render()
{
    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, m_elementCount, GL_UNSIGNED_SHORT, (void*)0);
}

void DebugBufferArrayBuffer()
{
    GLfloat* buf = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

    for (int i = 0; i < 4; i++) {
        qDebug() << buf[6*i] << "," << buf[6*i+1] << "," << buf[6*i+2] << " // "
                 << buf[6*i+3] << "," << buf[6*i+4] << "," << buf[6*i+5];
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void DebugIndexBuffer() {
    GLuint* buf = (GLuint*) glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);

    for (int i = 0; i < 2; i++) {
        qDebug() << buf[3*i] << "," << buf[3*i+1] << "," << buf[3*i+2];
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void OBJModel::createBuffers(mesh_t *mesh)
{
    qDebug() << mesh->vcount << mesh->icount;

    int totalSize = mesh->vcount * 3; // number of vertices * 3 float
    int stride = 0;
    int nOffset = 3;
    int tOffset = 3;

    if (mesh->normals != nullptr) {
        totalSize += mesh->vcount * 3; // number of normals * 3 float
        stride = 6;
        tOffset = 6;
    }

    if (mesh->texcoords != nullptr) {
        totalSize += mesh->vcount * 2; // number of tex coords * 2 float
        stride = (stride > 0) ? stride + 2 : 5;
    }

    qDebug() << "total size:" << totalSize;
    qDebug() << "stride:" << stride;

    GLfloat vertexData[totalSize];

    int voffset = stride > 0 ? stride : 3;

    for (int i = 0; i < mesh->vcount; i++) {
        vertexData[voffset * i    ] = mesh->vertices[i].x;
        vertexData[voffset * i + 1] = mesh->vertices[i].y;
        vertexData[voffset * i + 2] = mesh->vertices[i].z;

        if (mesh->normals != nullptr) {
            vertexData[i * stride + nOffset    ] = mesh->normals[i].x;
            vertexData[i * stride + nOffset + 1] = mesh->normals[i].y;
            vertexData[i * stride + nOffset + 2] = mesh->normals[i].z;
        }

        if (mesh->texcoords != nullptr) {
            vertexData[i * stride + tOffset + 0] = mesh->texcoords[i].u;
            vertexData[i * stride + tOffset + 1] = mesh->texcoords[i].v;
        }
    }

    /*
    for (int i = 0; i <= totalSize-stride; i += stride) {
        qDebug() << vertexData[i] << "," << vertexData[i+1] << "," << vertexData[i+2] << " // "
                 << vertexData[i+3] << "," << vertexData[i+4] << "," << vertexData[i+5];
    }
    */

    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);

    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), nullptr);

    if (mesh->normals != nullptr) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * nOffset));
    }

    if (mesh->texcoords != nullptr) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * tOffset));
    }

    GLuint tmpIndecies[mesh->icount];

    for (int i = 0; i < mesh->icount; i++) {
        tmpIndecies[i] = mesh->indecies[i];
    }

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * mesh->icount, mesh->indecies, GL_STATIC_DRAW);
    m_elementCount = mesh->icount;
    qDebug() << "element count" << m_elementCount;

    //DebugBufferArrayBuffer();
    //DebugIndexBuffer();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}












