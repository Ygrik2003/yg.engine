#pragma once

#include "render/types.hxx"

namespace yg::render
{

class index_buffer
{
public:
    virtual void bind() const = 0;

protected:
    std::uint32_t handle{ 0 };
};

} // namespace yg::render
