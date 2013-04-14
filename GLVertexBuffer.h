#ifndef GLBUFFER_H
#define GLBUFFER_H
#include "battlecraft.h"

class GLVertexBuffer
{
public:
    GLVertexBuffer(int type);
    ~GLVertexBuffer();
    void bind();
    void draw();
    void point(int attribute, int type, int elements, int offset, int stride, bool normalize);
    void bufferData(void* data, int elementSize, int elements);

protected:
    uint bufferRef;
    int size;
    int elements;
    int primitiveType;
};

#endif