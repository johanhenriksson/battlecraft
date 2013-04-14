#ifndef SHADERCOMPONENT_H
#define SHADERCOMPONENT_H
#include "battlecraft.h"

class ShaderComponent
{
public:
    ShaderComponent(uint programRef, GLenum type, const char* source);
    ~ShaderComponent();
    bool compile();

private:
    uint programRef;
    uint shaderRef;
    GLenum type;  
    const char* sourcePath;
};

#endif