#include "Tileset.h"

Tileset::Tileset(int size)
{
    this->palette = (Color*)calloc(size,3);
    this->health = (byte*)calloc(size,1);
}

Tileset::~Tileset()
{
    free(this->palette);
    free(this->health);
}

Color* Tileset::get(byte id)
{
    return &this->palette[id];
}

void Tileset::set(byte id, byte r, byte g, byte b)
{
    this->palette[id].r = r;
    this->palette[id].g = g;
    this->palette[id].b = b;
}

byte Tileset::getHealth(byte id)
{
    return this->health[id];
}

void Tileset::setHealth(byte id, byte hp)
{
    this->health[id] = hp;
}

