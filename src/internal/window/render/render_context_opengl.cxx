#include "render_context_opengl.hxx"

#include "window/render/vertex_buffer.hxx"

#include "glad/glad.h"

yg::render_context::result_code yg::render_context_opengl::initialize()
{
    GLuint vertex_buff = 0;
    glGenBuffers(1, &vertex_buff);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buff);

    GLuint vertex_array_object = 0;
    glGenVertexArrays(1, &vertex_array_object);

    glBindVertexArray(vertex_array_object);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, 600, 600);

    return result_code::SUCCESS;
}

yg::render_context::result_code yg::render_context_opengl::render_triangle()
{
    return result_code();
}
