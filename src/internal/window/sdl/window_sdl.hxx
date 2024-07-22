#pragma once

#include "window/window_manager.hxx"

namespace yg
{
class window_sdl : public window
{
public:
    window_sdl(yg::render::context::api api) noexcept;
    ~window_sdl() noexcept;
    window_sdl(const window_sdl& ctx)  = delete;
    window_sdl(const window_sdl&& ctx) = delete;

    result_code initialize(window_config& config) override;
    result_code capture_render_context(yg::render::context* ctx) override;

    bool process_events() override;
    void swap_buffers() override;

private:
    uint32_t window_flags{ 0 };
    void*    wnd;
    void*    gl_context;

    yg::color::rgba background_color;
};
} // namespace yg