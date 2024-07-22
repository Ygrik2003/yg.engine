#pragma once

#include "base_types.hxx"
#include "render/render_context.hxx"

#include <algorithm>
#include <cstdint>

namespace yg
{
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
        // SFML,
        SDL
    };
    virtual result_code initialize(window_config& config)                = 0;
    virtual result_code capture_render_context(yg::render::context* ctx) = 0;

    virtual bool process_events() = 0;
    virtual void swap_buffers()   = 0;

    window_api get_api() const noexcept { return api; }

protected:
    window_api api;
};

class window_manager
{
public:
    window_manager(window_config&   config,
                   window*          backend,
                   render::context* ctx);
};

} // namespace yg