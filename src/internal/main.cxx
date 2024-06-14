#if defined(YG_ENGINE_MAIN)

#include "base_types.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "window/sdl/window_sdl.hxx"
#include "window/window_manager.hxx"

#include "render/types.hxx"

#include "argparse/argparse.hxx"

#include "spdlog/spdlog.h"
#include <catch2/catch_session.hpp>
#include <libassert/assert.hpp>

#include <chrono>
#include <thread>
int main(int argc, char* argv[])
{
    argparse::ArgumentParser command_parser("Engine Runner");
    command_parser.add_argument("--unit_tests")
        .help("Engine Runner run UnitTests")
        .default_value(false);

    try
    {
        command_parser.parse_args(argc, argv);
    }
    catch (const std::exception& err)
    {
        spdlog::critical(err.what());
        ASSERT("Non valid command arguments");
    }

    yg::window_config wnd_cfg;
    wnd_cfg.size_x = 600;
    wnd_cfg.size_y = 600;

    yg::window* wnd_sdl =
        new yg::window_sdl(yg::render_context::render_api::OpenGL);
    yg::render_context* ctx_opengl = new yg::render_context_opengl();

    auto wnd_manager = new yg::window_manager(wnd_cfg, wnd_sdl, ctx_opengl);

    if (command_parser.is_used("--unit_tests"))
    {
        int result = Catch::Session().run();
    }
    // else
    // {
    //     while (wnd_sdl->process_events())
    //     {
    //         using namespace std::chrono;
    //         using namespace std::this_thread;

    //         sleep_for(milliseconds(1000 / wnd_cfg.fps));
    //     }
    // }
    return 0;
}

#endif