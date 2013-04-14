#version 150 core

const vec3 normals[6] = vec3[6]
(
    vec3(0,1,0), // up
    vec3(0,-1,0), // down
    vec3(1,0,0), // north
    vec3(-1,0,0), // south
    vec3(0,0,1), // east
    vec3(0,0,-1) // west
);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4 in_position;
in vec3 in_color;
in float in_light;
in int in_normalid;

out vec3 pass_color;
out vec3 pass_normal;
out float pass_light;

void main()
{
    pass_color = in_color;
    pass_light = in_light;
    pass_normal = normals[in_normalid];

    // Optimized mvp
    vec4 modelSpace = model * vec4(in_position);
    vec4 viewSpace = view * modelSpace;
    gl_Position = projection * viewSpace;
}