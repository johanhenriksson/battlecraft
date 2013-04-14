#ifndef GLVERTEXARRAY_H
#define GLVERTEXARRAY_H
#include "battlecraft.h"
#include "GLVertexBuffer.h"

class GLVertexArray
{
public:
    GLVertexArray();
    ~GLVertexArray();
    void bind();
    virtual void draw();

protected:
    virtual void enable();
    virtual void disable();

    uint arrayRef;
};

#endif