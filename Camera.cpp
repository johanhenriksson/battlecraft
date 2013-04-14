#include "Camera.h"

Camera::Camera(int width, int height, float fov)
{
    position    = vec3(5.0f,  3.0f,  4.0f);
    forward     = vec3(0.0f,  0.0f, -1.0f);
    right       = vec3(1.0f,  0.0f,  0.0f);
    up          = vec3(0.0f,  1.0f,  0.0f);
    lookat      = vec3(0.0f,  0.0f,  0.0f);
    angle       = vec3(3.5f, -0.4f,  0.0f);
    speed       = 6.0f;
    mouseSpeed  = 0.0038f;
    lastX       = 0;
    lastY       = 0;

    this->width = width;
    this->height = height;

    float aspectRatio = width/height;
    projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 32.0f);
}

vec3 Camera::getPosition()
{
    return position;
}

mat4* Camera::view()
{
    return &viewMatrix;
}

mat4* Camera::projection()
{
    return &projectionMatrix;
}

bool Camera::unProject(int x, int y, vec3* destination)
{
    float depth = 0.0f;
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    
    if (depth > 0.999f)
        return false;

    printf("depth: %f\n", depth);
    vec4 viewport = vec4(0, 0, width, height);
    vec3 point = vec3(x, y, depth);

    *destination = glm::unProject(point, viewMatrix, projectionMatrix, viewport);
    return true;
}

void Camera::update(float dt)
{
    forward.x = sinf(angle.x);
    forward.y = 0;
    forward.z = cosf(angle.x);

    right.x = -forward.z;
    right.y = 0;
    right.z = forward.x;

    lookat.x = sinf(angle.x) * cosf(angle.y);
    lookat.y = sinf(angle.y);
    lookat.z = cosf(angle.x) * cosf(angle.y);

    vec3 target = position + lookat;
    viewMatrix = glm::lookAt(position, target, up);

    handleMouse(dt);
    handleKeyboard(dt);
}

void Camera::handleMouse(float dt)
{
    int mx, my, dx, dy;
    glfwGetMousePos(&mx, &my);
    dx = mx - lastX;
    dy = my - lastY;

    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
    {
        angle.x -= dx * mouseSpeed;
        angle.y -= dy * mouseSpeed;

        if (angle.x < -PI) angle.x += PI * 2.0f;
        if (angle.x >  PI) angle.x -= PI * 2.0f;
        if (angle.y < PI * -0.49f) angle.y = PI * -0.49f;
        if (angle.y > PI *  0.49f) angle.y = PI *  0.49f;
    }

    lastX = mx;
    lastY = my;
}

void Camera::handleKeyboard(float dt)
{
    if (glfwGetKey('W') == GLFW_PRESS)
        position = position + forward * speed * dt;
    
    if (glfwGetKey('S') == GLFW_PRESS)
        position = position - forward * speed * dt;
    
    if (glfwGetKey('D') == GLFW_PRESS)
        position = position + right * speed * dt;

    if (glfwGetKey('A') == GLFW_PRESS)
        position = position - right * speed * dt;  

    if (glfwGetKey('E') == GLFW_PRESS)
        position = position + up * speed * dt; 

    if (glfwGetKey('Q') == GLFW_PRESS)
        position = position - up * speed * dt;
}
