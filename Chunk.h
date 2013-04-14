#ifndef CHUNK_H
#define CHUNK_H
#include "battlecraft.h"
#include "Tileset.h"
#include "VoxelShader.h"
#include "VoxelObject.h"

class Chunk
{
public:
    Chunk(Tileset* tileset, int sizeX, int sizeY, int sizeZ);
    ~Chunk();

    int getSizeX();
    int getSizeY();
    int getSizeZ();

    byte get(int x, int y, int z);
    void set(int x, int y, int z, byte type);

    void setPosition(vec3 position);
    vec3 getPosition();

    void compute();
    void draw(VoxelShader* shader);

protected:
    int sizeX;
    int sizeY;
    int sizeZ;
    int triangles;
    bool changed;
    Tileset* tileset;

    VoxelObject* geometry;
    byte* blocks;
    byte* hp;

    mat4 model;
    vec3 position;
};

#endif