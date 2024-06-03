#version 300 es
precision highp float;

in vec2 i_position;
in vec4 i_color;

out vec4 color;

void main()
{
    vec4 res_position = vec4(i_position.x / 2., i_position.y / 2., 0., 1.);
    gl_Position       = res_position;
    color             = vec4(0., 0., 0., 1.);
}