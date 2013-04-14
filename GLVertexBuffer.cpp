#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(int type)
{
    primitiveType = type;
    size = 0;
    elements = 0;
    glGenBuffers(1, &bufferRef);
    bind();
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &bufferRef);
}

void GLVertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferRef);
}

void GLVertexBuffer::draw()
{
    glDrawArrays(primitiveType, 0, elements);
}

void GLVertexBuffer::bufferData(void* data, int elementSize, int elements)
{
    this->size = elementSize;
    this->elements = elements;
    bind();
    glBufferData(GL_ARRAY_BUFFER, elements * elementSize, data, GL_STATIC_DRAW);
}

void GLVertexBuffer::point(int attribute, int type, int elements, int offset, int stride, bool normalize)
{
    glVertexAttribPointer(attribute, elements, type, normalize, stride, (const GLvoid*)offset);
}