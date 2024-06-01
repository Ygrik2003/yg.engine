#include "shader_opengl.hxx"

#include "render/types.hxx"

#include "glad/glad.h"
#include "spdlog/spdlog.h"

yg::shader_opengl::shader_opengl()
{
    program = glCreateProgram();
    YG_GL_CHECK_ERRORS();
}

yg::shader_opengl::~shader_opengl()
{
    glDeleteProgram(program);
    YG_GL_CHECK_ERRORS();
}

std::int32_t yg::shader_opengl::link()
{
    glLinkProgram(program);
    YG_GL_CHECK_ERRORS();

    std::int32_t is_linked{ 0 };
    glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
    if (is_linked == 0)
    {
        GLint max_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

        glDeleteProgram(program);

        spdlog::error(info_log.data());
    }
    return is_linked;
}

void yg::shader_opengl::add_compiled_shader(const compiled_shader& shader)
{
    shader.attach(program);
}
