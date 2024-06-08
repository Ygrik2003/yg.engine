#if defined(YG_ENGINE_MAIN)

#include "base_types.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "window/sdl/window_sdl.hxx"
#include "window/window_manager.hxx"

#include "render/types.hxx"

#include <catch2/catch_session.hpp>

#include <chrono>
#include <thread>

int main()
{
    yg::window_config wnd_cfg;
    wnd_cfg.size_x = 600;
    wnd_cfg.size_y = 600;

    yg::window* wnd_sdl =
        new yg::window_sdl(yg::render_context::render_api::OpenGL);
    yg::render_context* ctx_opengl = new yg::render_context_opengl();

    auto wnd_manager = new yg::window_manager(wnd_cfg, wnd_sdl, ctx_opengl);

#ifdef __YG_UNIT_TESTS__
    int result = Catch::Session().run();
#else
    while (wnd_sdl->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;

        sleep_for(milliseconds(1000 / wnd_cfg.fps));
    }
#endif
    return 0;
}

#endif