#include "VoxelObject.h"

VoxelObject::VoxelObject() 
    : GLVertexArray()
{
    voxelBuffer = new GLVertexBuffer(GL_TRIANGLES);
    voxelBuffer->point(VOXELSH_ATTR_POSITION, GL_UNSIGNED_BYTE, 3, 0, VOXELSH_VERTEX_SIZE, GL_FALSE);
    voxelBuffer->point(VOXELSH_ATTR_COLOR,    GL_UNSIGNED_BYTE, 3, 3, VOXELSH_VERTEX_SIZE, GL_TRUE);
    voxelBuffer->point(VOXELSH_ATTR_LIGHT,    GL_UNSIGNED_BYTE, 1, 6, VOXELSH_VERTEX_SIZE, GL_TRUE);
    voxelBuffer->point(VOXELSH_ATTR_NORMAL,   GL_UNSIGNED_BYTE, 1, 7, VOXELSH_VERTEX_SIZE, GL_FALSE);
}

VoxelObject::~VoxelObject()
{
    delete voxelBuffer;
}

void VoxelObject::draw()
{
    bind();
    enable();
    voxelBuffer->draw();
    disable();
}

void VoxelObject::bufferData(byte* data, int elements)
{
    voxelBuffer->bufferData((void*)data, VOXELSH_VERTEX_SIZE, elements);
}

void VoxelObject::enable()
{
    glEnableVertexAttribArray(VOXELSH_ATTR_POSITION);
    glEnableVertexAttribArray(VOXELSH_ATTR_COLOR);
    glEnableVertexAttribArray(VOXELSH_ATTR_LIGHT);
    glEnableVertexAttribArray(VOXELSH_ATTR_NORMAL);
}

void VoxelObject::disable()
{
    glDisableVertexAttribArray(VOXELSH_ATTR_NORMAL);
    glDisableVertexAttribArray(VOXELSH_ATTR_LIGHT);
    glDisableVertexAttribArray(VOXELSH_ATTR_COLOR);
    glDisableVertexAttribArray(VOXELSH_ATTR_POSITION);
}