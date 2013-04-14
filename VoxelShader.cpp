#include "VoxelShader.h"

VoxelShader::VoxelShader()
{
    this->program = glCreateProgram();
    this->uniformLocations = new map<const char*, uint>();

    // Shader specific
    this->vertexShader = new ShaderComponent(this->program, GL_VERTEX_SHADER, "voxel.v.glsl");
    this->fragmentShader = new ShaderComponent(this->program, GL_FRAGMENT_SHADER, "voxel.f.glsl");

    glBindAttribLocation(this->program, VOXELSH_ATTR_POSITION, "in_position");
    glBindAttribLocation(this->program, VOXELSH_ATTR_COLOR, "in_color");
    glBindAttribLocation(this->program, VOXELSH_ATTR_LIGHT, "in_light");
    glBindAttribLocation(this->program, VOXELSH_ATTR_NORMAL, "in_normalid");
}

VoxelShader::~VoxelShader()
{
    delete vertexShader;
    delete fragmentShader;
    glDeleteProgram(program);
}

void VoxelShader::compile()
{
    printf("Compiling Voxel shader...\n");
    this->vertexShader->compile();
    this->fragmentShader->compile();

    int status;
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        int length;
        char* buffer = (char*)malloc(1024);
        glGetProgramInfoLog(this->program, 1024, &length, buffer);
        printf("Shader link error: %s\n", buffer);
        free(buffer);
        return;
    }
    glValidateProgram(this->program);
    printf("Shader linked successfully.\n");
}

void VoxelShader::use()
{
    glUseProgram(this->program);
}

int VoxelShader::getUniform(const char* name)
{
    return glGetUniformLocation(program, name);
}

void VoxelShader::setUniformMatrix(const char* uniform, mat4* matrix)
{
    glUniformMatrix4fv(getUniform(uniform), 1, GL_FALSE, glm::value_ptr(*matrix));
}