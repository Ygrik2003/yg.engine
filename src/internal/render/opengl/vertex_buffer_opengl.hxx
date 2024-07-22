#pragma once

#include "render/types.hxx"
#include "render/vertex_buffer.hxx"

namespace yg::render::opengl
{
template <typename vertex_type>
class vertex_buffer_impl : public vertex_buffer<vertex_type>
{
public:
    vertex_buffer_impl(const vertex_type* vertices, std::size_t count);
    ~vertex_buffer_impl();
    inline void bind() override;
};

} // namespace yg::render::opengl
