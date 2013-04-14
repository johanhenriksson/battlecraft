#include "Shader.h"

Shader::Shader(const char* vs_source, const char* fs_source)
{
    program = glCreateProgram();
    compiled = false;
    vertex = new ShaderComponent(program, GL_VERTEX_SHADER, vs_source);
    fragment = new ShaderComponent(program, GL_FRAGMENT_SHADER, fs_source);
}

Shader::~Shader()
{
    delete vertex;
    delete fragment;
    glDeleteProgram(program);
}

void Shader::use()
{
    glUseProgram(program);
}

bool Shader::compile()
{
    if (compiled) return false;
    printf("Compiling shader %d...", program);
    vertex->compile();
    fragment->compile();

    int status;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        int length;
        char* buffer = (char*)malloc(1024);
        glGetProgramInfoLog(program, 1024, &length, buffer);
        printf("Shader link error: %s\n", buffer);
        free(buffer);
        return false;
    }
    glValidateProgram(program);
    printf("Shader linked successfully.\n");
    compiled = true;
    return true;
}

void Shader::setUniformMatrix(const char* uniform, mat4* matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(program, uniform), 1, GL_FALSE, glm::value_ptr(*matrix));
}