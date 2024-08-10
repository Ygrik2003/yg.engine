#pragma once

#include "base_types.hxx"
#include "render/render_context.hxx"
#include "window/events/keyboard.hxx"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>

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
        SDL,
        none,
    };
    virtual result_code initialize(window_config& config)                = 0;
    virtual result_code capture_render_context(yg::render::context* ctx) = 0;

    virtual bool process_events() = 0;
    virtual void swap_buffers()   = 0;

    // Callbacks
    virtual void on_resize(
        std::function<void(std::size_t, std::size_t)> func) = 0;

    window_api get_api() const noexcept { return api; }

protected:
    window_api api{ window_api::none };

    // Functions for callbacks
    std::vector<std::function<void(std::size_t, std::size_t)>> to_resize;
};

class window_manager
{
public:
    window_manager(window_config&   config,
                   window*          backend,
                   render::context* ctx);
};

} // namespace yg