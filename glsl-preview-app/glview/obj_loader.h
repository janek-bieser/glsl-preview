#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup OBJ-Loader
 *  @{
 */

/*!
 * \brief Possible states for mesh_loader_result.
 */
typedef enum mesh_loader_status
{
    MESH_LOADER_SUCCESS,
    MESH_LOADER_CANT_OPEN_FILE,
    MESH_LOADER_IO_ERROR,
    MESH_LOADER_PARSE_ERROR
} mesh_loader_status_t;

/*!
 * \brief Represents a vertex inside an OBJ file.
 */
typedef struct obj_vertex {
    float x;
    float y;
    float z;
} obj_vertex_t;

/*!
 * \brief Represents a texture coordinate inside an OBJ file.
 */
typedef struct obj_tex_coord {
    float u;
    float v;
} obj_tex_coord_t;

/*!
 * \brief Represents a mesh.
 */
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

/*!
 * \brief Result of a NewMeshFromOBJFile call.
 */
typedef struct mesh_loader_result
{
    mesh_t mesh;
    mesh_loader_status_t status;
} mesh_loader_result_t;

/*!
 * \brief Create a new mesh from an OBJ file.
 * \param filename Path to the OBJ file.
 * \return A mesh loader result.
 */
mesh_loader_result_t NewMeshFromOBJFile(const char* filename);

/*!
 * \brief Deletes a mesh.
 * \param mesh The mesh to delete.
 */
void DeleteMesh(mesh_t* mesh);

/** @}*/

#ifdef __cplusplus
}
#endif
