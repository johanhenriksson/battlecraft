#ifndef SHADER_H
#define SHADER_H
#include "battlecraft.h"
#include "ShaderComponent.h"

class Shader
{
public:
    Shader(const char* vs_source, const char* fs_source);
    ~Shader();
    bool compile();
    void use();

    void setUniformMatrix(const char* uniform, mat4* matrix);

protected:
    const char* name;
    uint program;
    bool compiled;
    ShaderComponent* vertex;
    ShaderComponent* fragment;
};

#endif