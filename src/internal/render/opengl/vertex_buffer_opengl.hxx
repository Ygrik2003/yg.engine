#pragma once

#include "render/types.hxx"
#include "render/vertex_buffer.hxx"

namespace yg
{
template <typename vertex_type>
class vertex_buffer_opengl : public vertex_buffer<vertex_type>
{
public:
    vertex_buffer_opengl(const vertex_type* vertices, std::size_t count);
    ~vertex_buffer_opengl();
    inline void bind() override;
};

} // namespace yg
