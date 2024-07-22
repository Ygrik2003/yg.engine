#if defined(YG_ENGINE_MAIN)

#include "base_types.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "render/types.hxx"
#include "tools/threads/unit_tests_thread.hxx"
#include "window/sdl/window_sdl.hxx"
#include "window/window_manager.hxx"

#include "argparse/argparse.hxx"
#include "libassert/assert.hpp"
#include "spdlog/spdlog.h"

#include <algorithm>
#include <chrono>
#include <thread>

void main_cycle(yg::window* wnd, yg::window_config wnd_cfg)
{
    while (wnd->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;

        wnd->swap_buffers();

        sleep_for(milliseconds(1000 / wnd_cfg.fps));
    }
}

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

    std::shared_ptr<yg::window> wnd_sdl =
        std::make_shared<yg::window_sdl>(yg::render::context::api::OpenGL);
    std::shared_ptr<yg::render::context> ctx_opengl =
        std::make_shared<yg::render::opengl::context_impl>();
    yg::window_manager wnd_manager(wnd_cfg, wnd_sdl.get(), ctx_opengl.get());

    if constexpr (yg::constants::is_unit_tests_binary)
    {
        std::unique_ptr<yg::unit_tests_thread> utt;
        if (command_parser.is_used("--unit_tests"))
        {
            utt = std::make_unique<yg::unit_tests_thread>();
        }
    }
    main_cycle(wnd_sdl.get(), wnd_cfg);

    return 0;
}

#endif