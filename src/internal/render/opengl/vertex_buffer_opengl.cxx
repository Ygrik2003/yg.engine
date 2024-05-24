#include "vertex_buffer_opengl.hxx"

#include <glad/glad.h>

namespace yg
{
template <typename vertex_type>
inline vertex_buffer_opengl<vertex_type>::vertex_buffer_opengl(
    const vertex_type* vertices, std::size_t count)
{
    glGenBuffers(1, &handle);
    GL_CHECK_ERRORS();

    bind();

    GLsizeiptr size_in_bytes =
        static_cast<GLsizeiptr>(count * sizeof(vertex_type));

    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
    GL_CHECK_ERRORS();
}

template <typename vertex_type>
inline void yg::vertex_buffer_opengl<vertex_type>::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, handle);
    GL_CHECK_ERRORS()
}

} // namespace yg
