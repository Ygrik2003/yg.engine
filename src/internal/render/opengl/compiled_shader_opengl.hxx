#pragma once

#include "render/compiled_shader.hxx"

namespace yg
{
class compiled_shader_opengl : compiled_shader
{
public:
    compiled_shader_opengl(const char* path, shader_type type);
    ~compiled_shader_opengl();

    void reload() override;
    void attach(std::uint32_t program) const noexcept override;

private:
    void load() override;

    std::int32_t shader_id;
};
} // namespace yg
