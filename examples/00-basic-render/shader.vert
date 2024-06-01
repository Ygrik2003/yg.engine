#version 300 es
precision highp float;

in vec3 i_position;
in vec4 i_color;

out vec3 v_position;

void main()
{
    gl_Position = vec4(v_position, 1.);
}