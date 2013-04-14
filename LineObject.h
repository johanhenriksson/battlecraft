#ifndef LINEOBJECT_H
#define LINEOBJECT_H
#include "battlecraft.h"
#include "GLVertexArray.h"
#include "GLVertexBuffer.h"
#include "LineShader.h"

/**
 * Line Shader Geometry Buffer
 */
class LineObject : public GLVertexArray
{
public:
    LineObject();
    ~LineObject();
    void draw();
    void bufferData(byte* data, int elements);

protected:
    GLVertexBuffer* geometry;
};

#endif