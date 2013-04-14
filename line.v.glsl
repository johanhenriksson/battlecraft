#version 150 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec4 in_position;
in vec4 in_color;

out vec4 pass_color;

void main()
{
    pass_color = in_color;
    
    // Optimized mvp
    vec4 modelSpace = model * vec4(in_position);
    vec4 viewSpace = view * modelSpace;
    gl_Position = projection * viewSpace;
}