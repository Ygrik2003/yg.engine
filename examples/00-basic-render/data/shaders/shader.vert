#version 300 es
precision highp float;

in vec2 i_position;
in vec4 i_color;

out vec4 color;

void main()
{
    float scale = 0.9;
    vec4  res_position =
        vec4(scale * i_position.x, scale * i_position.y, 0., 1.);
    color       = i_color;
    gl_Position = res_position;
}