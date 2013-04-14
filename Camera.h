#ifndef CAMERA_H
#define CAMERA_H
#include "battlecraft.h"
#include "Component.h"

#define MOUSE_MAX_DELTA = 25

class Camera : public Component
{
public:
    Camera(int width, int height, float fov);
    vec3 getPosition();
    mat4* view();
    mat4* projection();

    void update(float dt);
    bool unProject(int x, int y, vec3* destination);

protected:
    void handleMouse(float dt);
    void handleKeyboard(float dt);

    int width;
    int height;
    mat4 viewMatrix;
    mat4 projectionMatrix;

    vec3 position;
    vec3 angle;
    vec3 forward;
    vec3 right;
    vec3 up;
    vec3 lookat;
    float speed;
    float mouseSpeed;

    int lastX;
    int lastY;
};

#endif