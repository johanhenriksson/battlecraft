#ifndef battlecraft_h
#define battlecraft_h

// Standard Library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctime>
#include <vector>
#include <map>

// OpenGL, GLFW, GLM
#define GLFW_INCLUDE_GL3
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

typedef unsigned char byte;
typedef unsigned int uint;

typedef struct 
{
    byte x;
    byte y;
    byte z;
    byte light;

    byte r;
    byte g;
    byte b;
    byte hp;
} VoxelVertex;

typedef struct
{
    byte r;
    byte g;
    byte b;
} Color;

#define PI 3.141592f
#define VOXELSH_VERTEX_SIZE 8
#define VOXELSH_ATTR_POSITION 1
#define VOXELSH_ATTR_LIGHT 2
#define VOXELSH_ATTR_COLOR 3
#define VOXELSH_ATTR_NORMAL 4

#define glErrorCheck(location) \
    int error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        printf("GL Error #%d: %s at %s\n", error, gluErrorString(error), location); \
        glfwTerminate(); \
        exit(1); \
    }
#endif