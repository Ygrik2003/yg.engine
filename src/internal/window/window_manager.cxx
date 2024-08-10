#include "window/window_manager.hxx"

#include "libassert/assert.hpp"

yg::window_manager::window_manager(window_config&       config,
                                   window*              backend,
                                   yg::render::context* ctx)
{

    ASSERT(backend->initialize(config) != window::result_code::ERROR &&
           "Can't initialize window backend");

    ASSERT(backend->capture_render_context(ctx) != window::result_code::ERROR &&
           "Can't capture render context");

    ASSERT(ctx->initialize(config) != yg::render::context::result_code::ERROR &&
           "Can't initialize render context");

    auto set_viewport_size = [ctx](std::size_t x, std::size_t y)
    { ctx->set_viewport(0, 0, x, y); };
    backend->on_resize(set_viewport_size);
}