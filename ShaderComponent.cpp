#include "ShaderComponent.h"

char* readFileAsString(const char* source, int* length)
{
    long f_size;
    char* code;
    size_t code_s, result;
    FILE* fp = fopen(source, "r");
    fseek(fp, 0, SEEK_END);
    f_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    code_s = sizeof(char) * f_size;
    code = (char*)malloc(code_s);
    result = fread(code, 1, f_size, fp);
    fclose(fp);
    *length = (int)f_size;
    return code;
}

ShaderComponent::ShaderComponent(uint programRef, GLenum type, const char* source)
{
    this->programRef = programRef;
    this->type = type;
    this->sourcePath = source;
    this->shaderRef = glCreateShader(type);
}

ShaderComponent::~ShaderComponent()
{
    glDeleteShader(this->shaderRef);
}

bool ShaderComponent::compile()
{
    int length;
    const GLchar* source = (const GLchar*)readFileAsString(this->sourcePath, &length);

    glShaderSource(this->shaderRef, 1, &source, &length);
    glCompileShader(this->shaderRef);

    int result;
    glGetShaderiv(this->shaderRef, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        char* buffer = (char*)malloc(1024);
        int length;
        glGetShaderInfoLog(this->shaderRef, 1024, &length, buffer);
        printf("Error compiling shader component: %s\n", buffer);
        free(buffer);
        return false;
    }

    glErrorCheck("component compilation")

    glAttachShader(this->programRef, this->shaderRef);
    printf("Shader %d compiled.\n", this->shaderRef);
    return true;
}