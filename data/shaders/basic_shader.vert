#version 300 es
precision highp float;

layout(location = 0) in vec2 i_position;
layout(location = 1) in vec2 i_uv;
layout(location = 2) in vec4 i_color;

out vec2 uv;
out vec4 color;

void main()
{
    uv          = i_uv;
    float scale = 0.9;
    vec4  res_position =
        vec4(scale * i_position.x, scale * i_position.y, 0., 1.);
    color       = i_color;
    gl_Position = res_position;
}