#pragma once

#include <cstdint>

namespace yg::render
{

enum shader_type
{
    VERTEX,
    FRAGMENT
};

class compiled_shader
{
public:
    virtual void reload()                                     = 0;
    virtual void attach(std::uint32_t program) const noexcept = 0;

    shader_type get_type() const noexcept { return type; }

protected:
    virtual void load() = 0;

    const char* path_to_shader;
    shader_type type;
};
} // namespace yg::render