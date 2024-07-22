#pragma once

#include "render/index_buffer.hxx"
#include "render/types.hxx"

namespace yg::render::opengl
{
class index_buffer_impl : index_buffer
{
public:
    index_buffer_impl(const std::uint16_t* indexes, std::size_t count);
    ~index_buffer_impl();

    void bind() const override;
};

} // namespace yg::render::opengl