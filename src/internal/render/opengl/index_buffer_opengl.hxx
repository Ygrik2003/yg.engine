#pragma once

#include "render/index_buffer.hxx"
#include "render/types.hxx"

class index_buffer_opengl : index_buffer
{
public:
    index_buffer_opengl(const std::uint16_t* indexes, std::size_t count);
    ~index_buffer_opengl();

    void bind() const override;

private:
    std::uint32_t handle{ 0 };
};
