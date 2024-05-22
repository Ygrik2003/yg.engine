#pragma once

#include "window/render/render_context.hxx"

#include <cstdint>

namespace yg
{

#pragma pack(push, 8)
struct window_config
{
    const char* name = "Tanchiki";

    uint16_t size_x;
    uint16_t size_y;

    bool is_fullscreen;
    bool is_resizeble;

    const uint8_t fps = 60;
};
#pragma pack(pop)

class window
{
public:
    enum [[nodiscard]] result_code
    {
        SUCCESS,
        ERROR
    };
    enum window_api
    {
        SFML,
        SDL
    };
    virtual result_code initialize(const window_config& config)     = 0;
    virtual result_code capture_render_context(render_context* ctx) = 0;

    virtual bool process_events() = 0;

    window_api get_api() const noexcept { return api; }

protected:
    window_api api;
};

class window_manager
{
public:
    window_manager(window_config config, window* backend, render_context* ctx);
};

} // namespace yg