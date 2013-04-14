#ifndef LINESHADER_H
#define LINESHADER_H
#include "battlecraft.h"
#include "Shader.h"

#define LINESH_VERTEX_SIZE   6
#define LINESH_ATTR_POSITION 1
#define LINESH_ATTR_COLOR    2

class LineShader : public Shader
{
public:
    LineShader()
        : Shader("line.v.glsl", "line.f.glsl")
    {
        glBindAttribLocation(this->program, LINESH_ATTR_POSITION, "in_position");
        glBindAttribLocation(this->program, LINESH_ATTR_COLOR,    "in_color");
    }
};

#endif