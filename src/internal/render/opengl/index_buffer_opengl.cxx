#include "render/opengl/index_buffer_opengl.hxx"
#include "index_buffer_opengl.hxx"

#include "glad/glad.h"

yg::render::opengl::index_buffer_impl::index_buffer_impl(
    const uint16_t* indexes, size_t count)
{
    glGenBuffers(1, &handle);
    YG_GL_CHECK_ERRORS();

    bind();

    GLsizeiptr size_in_bytes = count * sizeof(std::uint16_t);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, size_in_bytes, indexes, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();
}
yg::render::opengl::index_buffer_impl::~index_buffer_impl()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    YG_GL_CHECK_ERRORS()
    glDeleteBuffers(1, &handle);
    YG_GL_CHECK_ERRORS()
}
void yg::render::opengl::index_buffer_impl::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    YG_GL_CHECK_ERRORS();
}