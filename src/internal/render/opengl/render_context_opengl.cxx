#include "render_context_opengl.hxx"

#include "render/vertex_buffer.hxx"

#include "glad/glad.h"

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
    YG_GL_CHECK_ERRORS()
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

// template <class vertex_type>
// void bind_texture_coords()
// {
//     glEnableVertexAttribArray(2);
//     YG_GL_CHECK_ERRORS();
//     glVertexAttribPointer(
//         2,
//         2,
//         GL_FLOAT,
//         GL_FALSE,
//         sizeof(vertex_type),
//         reinterpret_cast<GLvoid*>(vertex_type::offset_texture));
//     YG_GL_CHECK_ERRORS();
// }

template <class vertex_type>
void bind_colors()
{
    glEnableVertexAttribArray(3);
    YG_GL_CHECK_ERRORS();
    glVertexAttribPointer(
        1,
        4,
        GL_UNSIGNED_BYTE,
        GL_TRUE,
        sizeof(vertex_type),
        reinterpret_cast<GLvoid*>(vertex_type::offset_for_color));
    YG_GL_CHECK_ERRORS();
}

yg::render_context::result_code yg::render_context_opengl::initialize()
{
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, 600, 600);

    return result_code::SUCCESS;
}

yg::render_context::result_code yg::render_context_opengl::render_triangle(
    const triangle<vertex2d_rgba>& tr)
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(tr), &tr, GL_STATIC_DRAW);
    YG_GL_CHECK_ERRORS();

    bind_vertexes<vertex2d_rgba>();
    bind_colors<vertex2d_rgba>();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    YG_GL_CHECK_ERRORS();
    return result_code();
}
