#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum mesh_loader_status
{
    MESH_LOADER_SUCCESS,
    MESH_LOADER_CANT_OPEN_FILE,
    MESH_LOADER_IO_ERROR,
    MESH_LOADER_PARSE_ERROR
} mesh_loader_status_t;

typedef struct obj_vertex {
    float x;
    float y;
    float z;
} obj_vertex_t;

typedef struct obj_tex_coord {
    float u;
    float v;
} obj_tex_coord_t;

typedef struct mesh
{
    obj_vertex_t* vertices;
    obj_vertex_t* normals;
    obj_tex_coord_t* texcoords;
    uint16_t* indecies;

    int32_t vcount;
    int32_t icount;

    int32_t _vmax;
    int32_t _imax;
} mesh_t;

typedef struct mesh_loader_result
{
    mesh_t mesh;
    mesh_loader_status_t status;
} mesh_loader_result_t;

mesh_loader_result_t NewMeshFromOBJFile(const char* filename);
void DeleteMesh(mesh_t* mesh);

#ifdef __cplusplus
}
#endif
