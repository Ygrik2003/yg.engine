#pragma once

#include "render/types.hxx"

template <typename vertex_type>
class vertex_buffer
{
public:
    virtual void bind() const = 0;

protected:
    std::uint32_t handle{ 0 };
};