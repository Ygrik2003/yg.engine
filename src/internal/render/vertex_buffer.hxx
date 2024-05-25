#pragma once

#include "render/types.hxx"

template <typename vertex_type>
class vertex_buffer
{
public:
    virtual void        bind() = 0;
    virtual std::size_t size() const { return length; }

protected:
    std::size_t length{ 0 };
};