#include "render/opengl/shader_opengl.hxx"

#include "render/types.hxx"

#include "glad/glad.h"
#include "shader_opengl.hxx"
#include "spdlog/spdlog.h"

yg::render::opengl::shader_impl::shader_impl()
{
    program = glCreateProgram();
    YG_GL_CHECK_ERRORS();
}

yg::render::opengl::shader_impl::~shader_impl()
{
    glDeleteProgram(program);
    YG_GL_CHECK_ERRORS();
}

void yg::render::opengl::shader_impl::use() const
{
    glLinkProgram(program);
    YG_GL_CHECK_ERRORS();

    glUseProgram(program);
    YG_GL_CHECK_ERRORS();
}
void yg::render::opengl::shader_impl::reload()
{
    glDeleteProgram(program);
    YG_GL_CHECK_ERRORS()

    program = glCreateProgram();
    YG_GL_CHECK_ERRORS()

    for (auto& [type, shader] : compiled_shaders)
    {
        shader->reload();
        shader->attach(program);
    }

    glLinkProgram(program);
    YG_GL_CHECK_ERRORS();

    use();
}
std::int32_t yg::render::opengl::shader_impl::link()
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

void yg::render::opengl::shader_impl::add_compiled_shader(
    compiled_shader* shader)
{
    compiled_shaders[shader->get_type()] = shader;
    shader->attach(program);
}

void yg::render::opengl::shader_impl::set_uniform1(const char*  name,
                                                   std::int32_t value)
{
}
void yg::render::opengl::shader_impl::set_uniform1(const char*   name,
                                                   std::uint32_t value)
{
}
void yg::render::opengl::shader_impl::set_uniform1(const char* name,
                                                   float       value)
{
}

void yg::render::opengl::shader_impl::set_uniform1v(const char*   name,
                                                    std::int32_t* value,
                                                    std::uint32_t count)
{
}
void yg::render::opengl::shader_impl::set_uniform1v(const char*    name,
                                                    std::uint32_t* value,
                                                    std::uint32_t  count)
{
}
void yg::render::opengl::shader_impl::set_uniform1v(const char*   name,
                                                    float*        value,
                                                    std::uint32_t count)
{
}

void yg::render::opengl::shader_impl::set_uniform2(const char*  name,
                                                   std::int32_t val1,
                                                   std::int32_t val2)
{
}
void yg::render::opengl::shader_impl::set_uniform2(const char*   name,
                                                   std::uint32_t val1,
                                                   std::uint32_t val2)
{
}
void yg::render::opengl::shader_impl::set_uniform2(const char* name,
                                                   float       val1,
                                                   float       val2)
{
}

void yg::render::opengl::shader_impl::set_uniform2v(const char*   name,
                                                    std::int32_t* val1,
                                                    std::int32_t* val2,
                                                    std::uint32_t count)
{
}
void yg::render::opengl::shader_impl::set_uniform2v(const char*    name,
                                                    std::uint32_t* val1,
                                                    std::uint32_t* val2,
                                                    std::uint32_t  count)
{
}
void yg::render::opengl::shader_impl::set_uniform2v(const char*   name,
                                                    float*        val1,
                                                    float*        val2,
                                                    std::uint32_t count)
{
}

void yg::render::opengl::shader_impl::set_uniform3(const char*  name,
                                                   std::int32_t val1,
                                                   std::int32_t val2,
                                                   std::int32_t val3)
{
}
void yg::render::opengl::shader_impl::set_uniform3(const char*   name,
                                                   std::uint32_t val1,
                                                   std::uint32_t val2,
                                                   std::uint32_t val3)
{
}
void yg::render::opengl::shader_impl::set_uniform3(const char* name,
                                                   float       val1,
                                                   float       val2,
                                                   float       val3)
{
}

void yg::render::opengl::shader_impl::set_uniform3v(const char*   name,
                                                    std::int32_t* val1,
                                                    std::int32_t* val2,
                                                    std::int32_t* val3,
                                                    std::uint32_t count)
{
}
void yg::render::opengl::shader_impl::set_uniform3v(const char*    name,
                                                    std::uint32_t* val1,
                                                    std::uint32_t* val2,
                                                    std::uint32_t* val3,
                                                    std::uint32_t  count)
{
}
void yg::render::opengl::shader_impl::set_uniform3v(const char*   name,
                                                    float*        val1,
                                                    float*        val2,
                                                    float*        val3,
                                                    std::uint32_t count)
{
}

void yg::render::opengl::shader_impl::set_uniform4(const char*  name,
                                                   std::int32_t val1,
                                                   std::int32_t val2,
                                                   std::int32_t val3,
                                                   std::int32_t val4)
{
}
void yg::render::opengl::shader_impl::set_uniform4(const char*   name,
                                                   std::uint32_t val1,
                                                   std::uint32_t val2,
                                                   std::uint32_t val3,
                                                   std::uint32_t val4)
{
}
void yg::render::opengl::shader_impl::set_uniform4(
    const char* name, float val1, float val2, float val3, float val4)
{
}

void yg::render::opengl::shader_impl::set_uniform4v(const char*   name,
                                                    std::int32_t* val1,
                                                    std::int32_t* val2,
                                                    std::int32_t* val3,
                                                    std::int32_t* val4,
                                                    std::uint32_t count)
{
}
void yg::render::opengl::shader_impl::set_uniform4v(const char*    name,
                                                    std::uint32_t* val1,
                                                    std::uint32_t* val2,
                                                    std::uint32_t* val3,
                                                    std::uint32_t* val4,
                                                    std::uint32_t  count)
{
}
void yg::render::opengl::shader_impl::set_uniform4v(const char*   name,
                                                    float*        val1,
                                                    float*        val2,
                                                    float*        val3,
                                                    float*        val4,
                                                    std::uint32_t count)
{
}
