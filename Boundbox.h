#ifndef BOUNDBOX_H
#define BOUNDBOX_H
#include "battlecraft.h"
#include "GLVertexArray.h"
#include "LineShader.h"

class Boundbox : public GLVertexArray
{
public:
    Boundbox(int sizex, int sizey, int sizez);
    ~Boundbox();
    void draw(LineShader* linesh);

protected:
    void create();
    void enable();
    void disable();

private:
    int sizeX, sizeY, sizeZ;
    GLVertexBuffer* geometry;
    mat4 model;
    vec3 position;
    Color color;
};

#endif