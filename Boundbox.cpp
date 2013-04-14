#include "Boundbox.h"
#define _vertex(x,y,z,color) \
buffer[s++] = x; buffer[s++] = y; buffer[s++] = z; \
buffer[s++] = color.r; buffer[s++] = color.g; buffer[s++] = color.b; buffer[s++] = 210; v++

Boundbox::Boundbox(int sizex, int sizey, int sizez)
{
    sizeX = sizex;
    sizeY = sizey;
    sizeZ = sizez;

    box = new LineObject();

    position = vec3(0);
    model = glm::translate(mat4(1.0f), position);
    color.r = 0; color.g = 255; color.b = 0;

    create();
}

Boundbox::~Boundbox()
{
    delete box;
}

void Boundbox::create()
{
    int s = 0, v = 0;
    int verticies = ((sizeX + 1) * 2 + (sizeZ + 1) * 2 + 16) * LINESH_VERTEX_SIZE;
    byte* buffer = (byte*)malloc(verticies);

    for(int x = 0; x <= sizeX; x++)
    {
        _vertex(x,0,0,color);
        _vertex(x,0,sizeZ,color);
    }
    for(int z = 0; z <= sizeZ; z++)
    {
        _vertex(0,0,z,color);
        _vertex(sizeX,0,z,color);
    }

    _vertex(0,0,0,color);
    _vertex(0,sizeY,0,color);
    _vertex(0,0,sizeZ,color);
    _vertex(0,sizeY,sizeZ,color);
    _vertex(sizeX,0,0,color);
    _vertex(sizeX,sizeY,0,color);
    _vertex(sizeX,0,sizeZ,color);
    _vertex(sizeX,sizeY,sizeZ,color);

    _vertex(0,sizeY,0,color);
    _vertex(0,sizeY,sizeZ,color);
    _vertex(0,sizeY,0,color);
    _vertex(sizeX,sizeY,0,color);
    _vertex(sizeX,sizeY,sizeZ,color);
    _vertex(0,sizeY,sizeZ,color);
    _vertex(sizeX,sizeY,sizeZ,color);
    _vertex(sizeX,sizeY,0,color);

    box->bufferData(buffer, v);
    free(buffer);
}

void Boundbox::draw(LineShader* linesh)
{
    linesh->setUniformMatrix("model", &model);
    box->draw();
}