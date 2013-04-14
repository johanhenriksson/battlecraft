#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &arrayRef);
    bind();
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &arrayRef);
}

void GLVertexArray::bind()
{
    glBindVertexArray(arrayRef);
}

void GLVertexArray::draw()
{

}

void GLVertexArray::enable()
{

}

void GLVertexArray::disable()
{

}