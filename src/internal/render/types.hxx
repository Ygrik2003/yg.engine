#pragma once

#include "glm/glm.hpp"

#include <array>

#ifdef DEBUG
#define YG_GL_CHECK_ERRORS()                                                   \
    {                                                                          \
        const GLenum err = glGetError();                                       \
        if (err != GL_NO_ERROR)                                                \
        {                                                                      \
            switch (err)                                                       \
            {                                                                  \
                case GL_INVALID_ENUM:                                          \
                    std::cerr << "GL_INVALID_ENUM" << std::endl;               \
                    break;                                                     \
                case GL_INVALID_VALUE:                                         \
                    std::cerr << "GL_INVALID_VALUE" << std::endl;              \
                    break;                                                     \
                case GL_INVALID_OPERATION:                                     \
                    std::cerr << "GL_INVALID_OPERATION" << std::endl;          \
                    break;                                                     \
                case GL_INVALID_FRAMEBUFFER_OPERATION:                         \
                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"            \
                              << std::endl;                                    \
                    break;                                                     \
                case GL_OUT_OF_MEMORY:                                         \
                    std::cerr << "GL_OUT_OF_MEMORY" << std::endl;              \
                    break;                                                     \
            }                                                                  \
            std::cerr << __FILE__ << ':' << __LINE__ << '(' << __FUNCTION__    \
                      << ')' << std::endl;                                     \
            assert(false);                                                     \
        }                                                                      \
    }
#else
#define YG_GL_CHECK_ERRORS()
#endif

namespace yg
{
struct vertex2d
{
    glm::vec2 pos;
};

struct vertex3d
{
    glm::vec3 pos;
};
struct vertex2d_uv_rgba
{
    glm::vec2     pos;
    glm::vec2     uv;
    std::uint32_t col;
};

struct vertex3d_uv_rgba
{
    glm::vec3     pos;
    glm::vec2     uv;
    std::uint32_t col;
};
struct vertex2d_uv
{
    glm::vec2 pos;
    glm::vec2 uv;
};

struct vertex3d_uv
{
    glm::vec3 pos;
    glm::vec2 uv;
};
struct vertex2d_rgba
{
    glm::vec2     pos;
    std::uint32_t col;
};

struct vertex3d_rgba
{
    glm::vec3     pos;
    std::uint32_t col;
};

template <typename vertex_type>
class triangle
{
public:
    triangle(vertex_type vert1, vertex_type vert2, vertex_type vert3)
        : values{ vert1, vert2, vert3 }
    {
    }
    inline vertex_type* data() const noexcept { return values.data(); }

private:
    std::array<vertex_type, 3> values;
};

} // namespace yg