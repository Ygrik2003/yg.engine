#version 300 es
precision mediump float;

in vec3 v_position;

out vec4 o_color;

void main()
{
    o_color = vec4(result, color.w);
}