#ifndef VOXELSHADER_H
#define VOXELSHADER_H
#include "battlecraft.h"
#include "ShaderComponent.h"

class VoxelShader
{
public:
    VoxelShader();
    ~VoxelShader();
    void compile();
    void use();
    void setUniformMatrix(const char* uniform, mat4* matrix);

protected:
    int getUniform(const char* name);

private:
    uint program;
    bool compiled;

    ShaderComponent* vertexShader;
    ShaderComponent* fragmentShader;
    map<const char*, uint>* uniformLocations;
};

#endif