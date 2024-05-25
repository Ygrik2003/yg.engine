#pragma once

#include "render/types.hxx"
#include "render/vertex_buffer.hxx"

namespace yg
{
template <typename vertex_type>
class vertex_buffer_opengl : public vertex_buffer<vertex_type>
{
public:
    inline vertex_buffer_opengl(const vertex_type* vertices, std::size_t count);
    inline void bind() override;

private:
    std::uint32_t handle{ 0 };
};

} // namespace yg
