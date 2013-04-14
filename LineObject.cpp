#include "LineObject.h"

LineObject::LineObject()
    : GLVertexArray()
{
    geometry = new GLVertexBuffer(GL_LINES);
    geometry->point(LINESH_ATTR_POSITION, GL_UNSIGNED_BYTE, 3, 0, LINESH_VERTEX_SIZE, GL_FALSE);
    geometry->point(LINESH_ATTR_COLOR,    GL_UNSIGNED_BYTE, 4, 3, LINESH_VERTEX_SIZE, GL_TRUE);
}

LineObject::~LineObject()
{
    delete geometry;
}

void LineObject::draw()
{
    bind();
    glEnableVertexAttribArray(LINESH_ATTR_POSITION);
    glEnableVertexAttribArray(LINESH_ATTR_COLOR);
    geometry->draw();
    glDisableVertexAttribArray(LINESH_ATTR_COLOR);
    glDisableVertexAttribArray(LINESH_ATTR_POSITION);
}

void LineObject::bufferData(byte* data, int elements)
{
    geometry->bufferData(data, LINESH_VERTEX_SIZE, elements);
}