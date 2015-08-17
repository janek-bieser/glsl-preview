#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "obj_loader.h"

// Private API Definition
// -----------------------------------------------------------------------------

static const mesh_t DEFAULT_MESH = { NULL, NULL, NULL, NULL, 0, 0, 0, 0 };
static const mesh_loader_result_t DEFAULT_RESULT = {
    { NULL, NULL, NULL, NULL, 0, 0, 0, 0 },
    MESH_LOADER_CANT_OPEN_FILE
};

typedef struct obj_info
{
    int vcount;
    int ncount;
    int tcount;
    int fcount;

    int vpos;
    int npos;
    int tpos;
    int fpos;

    int felem_count;
} obj_info_t;

typedef struct obj_face
{
    obj_vertex_t v1;
    obj_vertex_t v2;
    obj_vertex_t v3;
} obj_face_t;

obj_info_t GetOBJInfo(FILE* obj_file);
mesh_t CreateMesh(FILE* obj_file, obj_info_t file_info);

// Public API Implementation
// -----------------------------------------------------------------------------

mesh_loader_result_t
NewMeshFromOBJFile(const char* filename)
{
    mesh_loader_result_t result = DEFAULT_RESULT;

    FILE* fp = fopen(filename, "r");
    if (!fp) { return result; }

    obj_info_t file_info = GetOBJInfo(fp);

    mesh_t mesh = CreateMesh(fp, file_info);
    result.mesh = mesh;

    if (mesh.vcount > 0) {
        result.status = MESH_LOADER_SUCCESS;
    } else {
        result.status = MESH_LOADER_PARSE_ERROR;
    }

    fclose(fp);
    return result;
}

void
DeleteMesh(mesh_t* mesh)
{
    if (mesh != NULL) {
        free(mesh->vertices);
        mesh->vertices = NULL;
        free(mesh->normals);
        mesh->normals = NULL;
        free(mesh->indecies);
        mesh->indecies = NULL;
    }
}

// Private API Implementation
// -----------------------------------------------------------------------------

static inline int GetFaceElementCount(const char* face_str)
{
    int a, b, c;
    if (sscanf(face_str, "f %d/%d/%d", &a, &b, &c) == 3) {
        return 3;
    } else if (sscanf(face_str, "f %d//%d", &a, &b) == 2) {
        return 2;
    }
    return 1;
}

obj_info_t
GetOBJInfo(FILE* obj_file)
{
    obj_info_t info = { 0, 0, 0, 0, 0, 0, 0, 0 };
    rewind(obj_file);

    char line[128];

    while (fgets(line, sizeof(line), obj_file)) {
        if (line[0] == 'v') {
            if (line[1] == 'n') {
                if (info.npos == 0) {
                    info.npos = ftell(obj_file) - strlen(line);
                }
                info.ncount++;
            } else if(line[1] == 't') {
                if (info.tpos == 0) {
                    info.tpos = ftell(obj_file) - strlen(line);
                }
                info.tcount++;
            } else {
                if (info.vpos == 0) {
                    info.vpos = ftell(obj_file) - strlen(line);
                }
                info.vcount++;
            }
        } else if (line[0] == 'f') {
            if (info.fpos == 0) {
                info.fpos = ftell(obj_file) - strlen(line);
                info.felem_count = GetFaceElementCount(line);
            }
            info.fcount++;
        }
    }

    rewind(obj_file);

    return info;
}

static inline bool
VertexEqual(obj_vertex_t* a, obj_vertex_t* b)
{
    return (a->x == b->x && a->y == b->y && a->z == b->z);
}

static inline bool
TexCoordEqual(obj_tex_coord_t* a, obj_tex_coord_t* b)
{
    return (a->u == b->u && a->v == b->v);
}

static inline int32_t
IndexOfFaceVertex(mesh_t* mesh, obj_vertex_t* vertex, obj_vertex_t* normal, obj_tex_coord_t* uv)
{
    if (uv == NULL) {
        for (int i = 0; i < mesh->vcount; i++) {
            if (VertexEqual(&mesh->vertices[i], vertex) &&
                VertexEqual(&mesh->normals[i], normal)) {
                return i;
            }
        }
    } else {
        for (int i = 0; i < mesh->vcount; i++) {
            if (VertexEqual(&mesh->vertices[i], vertex) &&
                VertexEqual(&mesh->normals[i], normal) &&
                TexCoordEqual(&mesh->texcoords[i], uv)) {
                return i;
            }
        }
    }

    return -1;
}                                

static inline mesh_t
AllocateMeshData(obj_info_t* info)
{
    mesh_t mesh = DEFAULT_MESH;
    mesh.vertices = calloc(info->vcount, sizeof(obj_vertex_t));
    mesh.normals  = calloc(info->vcount, sizeof(obj_vertex_t));

    if (info->felem_count > 2) { // has texture coords
        mesh.texcoords = calloc(info->vcount, sizeof(obj_tex_coord_t));
    }
    
    mesh.indecies = calloc(info->fcount*3, sizeof(uint16_t));

    return mesh;
}

static inline void
ReallocMeshData(mesh_t* mesh)
{
    size_t newSize = (mesh->vcount * 2 > 0) ? mesh->vcount * 2 : 32; 
    mesh->vertices = realloc(mesh->vertices, sizeof(obj_vertex_t) * newSize);
    mesh->normals = realloc(mesh->normals, sizeof(obj_vertex_t) * newSize);
    if (mesh->texcoords != NULL) {
        mesh->texcoords = realloc(mesh->texcoords, sizeof(obj_tex_coord_t) * newSize);
    }
    mesh->_vmax = newSize;
}

static inline int32_t
AddVertexToMesh(mesh_t* mesh, obj_vertex_t* vertex, obj_vertex_t* normal, obj_tex_coord_t* uv)
{
    if (mesh->vcount >= mesh->_vmax) {
        ReallocMeshData(mesh);
    }

    mesh->vertices[mesh->vcount] = *vertex;
    mesh->normals[mesh->vcount] = *normal;

    if (uv != NULL) {
        mesh->texcoords[mesh->vcount] = *uv;
    }

    mesh->vcount++;
    
    return (mesh->vcount-1);
}

static inline void
AddIndexToMesh(mesh_t* mesh, obj_vertex_t* vertex, obj_vertex_t* normal, obj_tex_coord_t* uv)
{
    int32_t idx = IndexOfFaceVertex(mesh, vertex, normal, uv);
    if (idx < 0) {
        idx = AddVertexToMesh(mesh, vertex, normal, uv);
    }
    mesh->indecies[mesh->icount] = idx;
    mesh->icount++;
}

mesh_t
CreateMesh(FILE* obj_file, obj_info_t file_info)
{
    obj_vertex_t tmpVertices[file_info.vcount];
    obj_vertex_t tmpNormals[file_info.ncount];
    printf("tcount: %d\n", file_info.tcount);
    obj_tex_coord_t tmpUVs[file_info.tcount];
    char line[128];

    // read vertices
    fseek(obj_file, file_info.vpos, SEEK_SET);
    for (int i = 0; i < file_info.vcount; i++) {
        fgets(line, sizeof(line), obj_file);
        sscanf(line, "v %f %f %f", &tmpVertices[i].x, &tmpVertices[i].y, &tmpVertices[i].z);
    }

    // read normals
    if (file_info.felem_count > 1) {
        fseek(obj_file, file_info.npos, SEEK_SET);
        for (int i = 0; i < file_info.ncount; i++) {
            fgets(line, sizeof(line), obj_file);
            sscanf(line, "vn %f %f %f", &tmpNormals[i].x, &tmpNormals[i].y, &tmpNormals[i].z);
        }
    }

    // read tex coords
    if (file_info.felem_count > 2) {
        fseek(obj_file, file_info.tpos, SEEK_SET);
        for (int i = 0; i < file_info.tcount; i++) {
            fgets(line, sizeof(line), obj_file);
            sscanf(line, "vt %f %f", &tmpUVs[i].u, &tmpUVs[i].v);
        }
    }

    //mesh_t mesh = CreateEmptyMesh(file_info.vcount, file_info.fcount * 3);
    mesh_t mesh = AllocateMeshData(&file_info);

    // read faces
    int32_t v[3];
    int32_t n[3];
    int32_t t[3];
    fseek(obj_file, file_info.fpos, SEEK_SET);

    for (int i = 0; i < file_info.fcount; i++) {
        fgets(line, sizeof(line), obj_file);

        if (file_info.felem_count == 2) {
            sscanf(line, "f %d//%d %d//%d %d//%d", &v[0], &n[0], &v[1], &n[1], &v[2], &n[2]);
            AddIndexToMesh(&mesh, &tmpVertices[v[0]-1], &tmpNormals[n[0]-1], NULL);
            AddIndexToMesh(&mesh, &tmpVertices[v[1]-1], &tmpNormals[n[1]-1], NULL);
            AddIndexToMesh(&mesh, &tmpVertices[v[2]-1], &tmpNormals[n[2]-1], NULL);
        } else if (file_info.felem_count == 3) {
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]);
            AddIndexToMesh(&mesh, &tmpVertices[v[0]-1], &tmpNormals[n[0]-1], &tmpUVs[t[0]-1]);
            AddIndexToMesh(&mesh, &tmpVertices[v[1]-1], &tmpNormals[n[1]-1], &tmpUVs[t[1]-1]);
            AddIndexToMesh(&mesh, &tmpVertices[v[2]-1], &tmpNormals[n[2]-1], &tmpUVs[t[2]-1]);
        }
    }

    return mesh;
}
