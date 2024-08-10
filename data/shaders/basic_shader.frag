#version 300 es
precision mediump float;

in vec4 color;
in vec2 uv;

uniform sampler2D u_texture;

out vec4 o_color;

void main()
{
    // o_color = (color + texture(u_texture, uv)) / 2.;
    o_color = texture(u_texture, uv);
}