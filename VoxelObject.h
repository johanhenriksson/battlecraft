#ifndef VOXELOBJ_H
#define VOXELOBJ_H
#include "battlecraft.h"
#include "GLVertexArray.h"
#include "GLVertexBuffer.h"

/**
 * Voxel Geometry Buffer
 * GLVertexArray for use with VoxelShader
 */
class VoxelObject : public GLVertexArray
{
public:
    VoxelObject();
    ~VoxelObject();
    void draw();
    void bufferData(byte* data, int elements);

protected:
    void enable();
    void disable();

    GLVertexBuffer* voxelBuffer;
};

#endif