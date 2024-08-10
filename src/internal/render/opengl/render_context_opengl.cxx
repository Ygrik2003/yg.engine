#include "render_context_opengl.hxx"

#include "render/vertex_buffer.hxx"

#include "glad/glad.h"

namespace yg::render::opengl
{

template <class vertex_type>
void bind_vertexes()
{
    glEnableVertexAttribArray(0);
    YG_GL_CHECK_ERRORS();
    glVertexAttribPointer(0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(vertex_type),
                          reinterpret_cast<GLvoid*>(0));
    YG_GL_CHECK_ERRORS();
}
// template <class vertex_type>
// void bind_normal()
// {
//     glEnableVertexAttribArray(1);
//     YG_GL_CHECK_ERRORS();
//     glVertexAttribPointer(
//         1,
//         3,
//         GL_FLOAT,
//         GL_FALSE,
//         sizeof(vertex_type),
//         reinterpret_cast<GLvoid*>(vertex_type::offset_normal));
//     YG_GL_CHECK_ERRORS();
// }

template <class vertex_type>
void bind_texture_coords()
{
    glEnableVertexAttribArray(1);
    YG_GL_CHECK_ERRORS();
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(vertex_type),
        reinterpret_cast<GLvoid*>(vertex_type::offset_for_texture));
    YG_GL_CHECK_ERRORS();
}

template <class vertex_type>
void bind_colors()
{
    glEnableVertexAttribArray(2);
    YG_GL_CHECK_ERRORS();
    glVertexAttribPointer(
        2,
        4,
        GL_UNSIGNED_BYTE,
        GL_TRUE,
        sizeof(vertex_type),
        reinterpret_cast<GLvoid*>(vertex_type::offset_for_color));
    YG_GL_CHECK_ERRORS();
}

context::result_code context_impl::initialize(const window_config& config)
{
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    YG_GL_CHECK_ERRORS();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    YG_GL_CHECK_ERRORS();

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    YG_GL_CHECK_ERRORS();

    glBindVertexArray(vao);
    YG_GL_CHECK_ERRORS();

    glEnable(GL_BLEND);
    YG_GL_CHECK_ERRORS();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    YG_GL_CHECK_ERRORS();

    glEnable(GL_DEPTH_TEST);
    YG_GL_CHECK_ERRORS();
    glDisable(GL_CULL_FACE);
    YG_GL_CHECK_ERRORS();

    glViewport(0, 0, config.size_x, config.size_y);
    YG_GL_CHECK_ERRORS();

    return result_code::SUCCESS;
}

void context_impl::set_viewport(std::size_t dx,
                                std::size_t dy,
                                std::size_t x,
                                std::size_t y) const
{
    glViewport(dx, dy, x, y);
    YG_GL_CHECK_ERRORS();
}

context::result_code context_impl::render_triangle(const triangle<vertex2d>& tr)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr), &tr, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();

    bind_vertexes<vertex2d>();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    YG_GL_CHECK_ERRORS();
    return result_code::SUCCESS;
}
context::result_code context_impl::render_triangle(
    const triangle<vertex2d_rgba>& tr)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr), &tr, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();

    bind_vertexes<vertex2d_rgba>();
    bind_colors<vertex2d_rgba>();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    YG_GL_CHECK_ERRORS();
    return result_code::SUCCESS;
}
context::result_code context_impl::render_triangle(
    const triangle<vertex2d_uv>& tr)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr), &tr, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();

    bind_vertexes<vertex2d_uv>();
    bind_texture_coords<vertex2d_uv>();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    YG_GL_CHECK_ERRORS();
    return result_code::SUCCESS;
}
context::result_code context_impl::render_triangle(
    const triangle<vertex2d_uv_rgba>& tr)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr), &tr, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();

    bind_vertexes<vertex2d_uv_rgba>();
    bind_texture_coords<vertex2d_uv_rgba>();
    bind_colors<vertex2d_uv_rgba>();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    YG_GL_CHECK_ERRORS();
    return result_code::SUCCESS;
}
} // namespace yg::render::opengl