#pragma once

#include "window/window_manager.hxx"

namespace yg
{
class window_sdl : public window
{
public:
    window_sdl(render_context::render_api render_api) noexcept;

    ~window_sdl() noexcept             = default;
    window_sdl(const window_sdl& ctx)  = delete;
    window_sdl(const window_sdl&& ctx) = delete;

    result_code initialize(const window_config& config) override;
    result_code capture_render_context(render_context* ctx) override;

    bool process_events() override;

private:
    uint32_t window_flags;
    void*    wnd;
    void*    gl_context;
};
} // namespace yg