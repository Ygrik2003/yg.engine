#pragma once

#include "render/types.hxx"

template <typename vertex_type>
class vertex_buffer
{
public:
    virtual void   bind() = 0;
    virtual size_t size() const { return length; }

protected:
    size_t length{ 0 };
};