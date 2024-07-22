#pragma once

#include "render/compiled_shader.hxx"

namespace yg::render::opengl
{
class compiled_shader_impl : public compiled_shader
{
public:
    compiled_shader_impl(const char* path, shader_type type);
    ~compiled_shader_impl();

    void reload() override;
    void attach(std::uint32_t program) const noexcept override;

private:
    void load() override;

    std::int32_t shader_id;
};
} // namespace yg::render::opengl
