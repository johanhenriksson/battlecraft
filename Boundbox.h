#ifndef BOUNDBOX_H
#define BOUNDBOX_H
#include "battlecraft.h"
#include "LineShader.h"
#include "LineObject.h"

class Boundbox : public GLVertexArray
{
public:
    Boundbox(int sizex, int sizey, int sizez);
    ~Boundbox();
    void draw(LineShader* linesh);

protected:
    void create();

private:
    int sizeX, sizeY, sizeZ;
    LineObject* box;
    mat4 model;
    vec3 position;
    Color color;
};

#endif