#include "compiled_shader_opengl.hxx"

#include "render/types.hxx"
#include "tools/filesystem/files_api.hxx"

#include "glad/glad.h"
#include "spdlog/spdlog.h"

yg::render::opengl::compiled_shader_impl::compiled_shader_impl(const char* path,
                                                               shader_type type)
{
    this->type           = type;
    this->path_to_shader = path;

    load();
}

yg::render::opengl::compiled_shader_impl::~compiled_shader_impl()
{
    glDeleteShader(shader_id);
    YG_GL_CHECK_ERRORS();
}

void yg::render::opengl::compiled_shader_impl::reload()
{
    glDeleteShader(shader_id);
    YG_GL_CHECK_ERRORS();

    load();
}

void yg::render::opengl::compiled_shader_impl::attach(
    std::uint32_t program) const noexcept
{
    glAttachShader(program, shader_id);
    YG_GL_CHECK_ERRORS();
}

void yg::render::opengl::compiled_shader_impl::load()
{
    std::string shader_code   = read_file(path_to_shader);
    const char* shader_code_c = shader_code.data();

    switch (type)
    {
        case shader_type::VERTEX:
            shader_id = glCreateShader(GL_VERTEX_SHADER);
            break;

        case shader_type::FRAGMENT:
            shader_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
    }
    YG_GL_CHECK_ERRORS();

    glShaderSource(shader_id, 1, &shader_code_c, nullptr);
    YG_GL_CHECK_ERRORS();

    glCompileShader(shader_id);
    YG_GL_CHECK_ERRORS();

    GLint result = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    YG_GL_CHECK_ERRORS();
    if (result == 0)
    {
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &result);
        YG_GL_CHECK_ERRORS()

        std::vector<GLchar> log(static_cast<size_t>(result));
        glGetShaderInfoLog(shader_id, result, nullptr, log.data());
        YG_GL_CHECK_ERRORS();

        glDeleteShader(shader_id);
        YG_GL_CHECK_ERRORS();

        spdlog::error(log.data());
    }
}