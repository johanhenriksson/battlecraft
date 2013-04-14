#include "Boundbox.h"
#define _vertex(x,y,z,color) \
buffer[s++] = x; buffer[s++] = y; buffer[s++] = z; \
buffer[s++] = color.r; buffer[s++] = color.g; buffer[s++] = color.b; v++

Boundbox::Boundbox(int sizex, int sizey, int sizez)
{
    sizeX = sizex;
    sizeY = sizey;
    sizeZ = sizez;
    geometry = new GLVertexBuffer(GL_LINES);
    position = vec3(0);
    model = glm::translate(mat4(1.0f), position);
    color.r = 0; color.g = 255; color.b = 0;

    create();
}

Boundbox::~Boundbox()
{
    delete geometry;
}

void Boundbox::create()
{
    int s = 0, v = 0;
    int verticies = ((sizeX + 1) * 2 + (sizeZ + 1) * 2 + 16) * LINESH_VERTEX_SIZE;
    byte* buffer = (byte*)malloc(verticies);

    for(int x = 0; x <= sizeX; x++)
    {
        for(int z = 0; z <= sizeZ; z++)
        {
            _vertex(x,0,z,color);
            _vertex(x,0,z+sizeZ,color);
        }
        _vertex(x,0,0,color);
        _vertex(x+sizeX,0,0,color);
    }

    geometry->bufferData(buffer, LINESH_VERTEX_SIZE, v);
    free(buffer);
}

void Boundbox::enable()
{
    glEnableVertexAttribArray(LINESH_ATTR_POSITION);
    glEnableVertexAttribArray(LINESH_ATTR_COLOR);
}

void Boundbox::disable()
{
    glDisableVertexAttribArray(LINESH_ATTR_COLOR);
    glDisableVertexAttribArray(LINESH_ATTR_POSITION);
}

void Boundbox::draw(LineShader* linesh)
{
    linesh->setUniformMatrix("model", &model);
    bind();
    enable();
    geometry->draw();
    disable();
}