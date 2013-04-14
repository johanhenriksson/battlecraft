#ifndef TILESET_H
#define TILESET_H
#include "battlecraft.h"

class Tileset
{
public:
    Tileset(int size);
    ~Tileset();
    
    Color* get(byte id);
    void set(byte id, byte r, byte g, byte b);
    byte getHealth(byte id);
    void setHealth(byte id, byte hp);

protected:
    byte id;
    Color* palette;
    byte* health;
};

#endif