#include "vertex_buffer_opengl.hxx"

#include <glad/glad.h>

template <typename vertex_type>
yg::render::opengl::vertex_buffer_impl<vertex_type>::vertex_buffer_impl(
    const vertex_type* vertices, std::size_t count)
{
    glGenBuffers(1, &this->handle);
    YG_GL_CHECK_ERRORS();

    bind();

    GLsizeiptr size_in_bytes =
        static_cast<GLsizeiptr>(count * sizeof(vertex_type));

    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();
}

template <class vertex_type>
yg::render::opengl::vertex_buffer_impl<vertex_type>::~vertex_buffer_impl()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    YG_GL_CHECK_ERRORS()
    glDeleteBuffers(1, &this->handle);
    YG_GL_CHECK_ERRORS()
}

template <typename vertex_type>
inline void yg::render::opengl::vertex_buffer_impl<vertex_type>::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->handle);
    YG_GL_CHECK_ERRORS();
}
