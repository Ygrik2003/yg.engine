#if defined(YG_ENGINE_MAIN)

#include "base_types.hxx"
#include "render/opengl/compiled_shader_opengl.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "render/opengl/shader_opengl.hxx"
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

void main_cycle(yg::window*          wnd,
                yg::render::context* ctx,
                yg::window_config    wnd_cfg)
{
    using namespace yg;
    using namespace render;

    auto* shader_opengl_vert = new render::opengl::compiled_shader_impl(
        "data/shaders/basic_shader.vert", render::shader_type::VERTEX);
    auto* shader_opengl_frag = new render::opengl::compiled_shader_impl(
        "data/shaders/basic_shader.frag", render::shader_type::FRAGMENT);

    auto shader_opengl = render::opengl::shader_impl();
    shader_opengl.add_compiled_shader(shader_opengl_vert);
    shader_opengl.add_compiled_shader(shader_opengl_frag);

    shader_opengl.use();

    auto rotate_matrix = [](double phi)
    {
        return glm::mat2x2(
            glm::cos(phi), -glm::sin(phi), glm::sin(phi), glm::cos(phi));
    };
    render::triangle<render::vertex2d_rgba> test_tr{
        { { 1., -1. }, 0xFF0000FF },
        { { 1., 1. }, 0xFFFF0000 },
        { { -1., -1. }, 0xFF00FF00 }
    };

    double delta_phi = 0.1;
    while (wnd->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;

        std::for_each(test_tr.begin(),
                      test_tr.end(),
                      [&rotate_matrix, delta_phi](render::vertex2d_rgba& vert)
                      { vert.pos = vert.pos * rotate_matrix(delta_phi); });

        auto result = ctx->render_triangle(test_tr);
        wnd->swap_buffers();
        sleep_for(milliseconds(1000 / wnd_cfg.fps)); // TODO: do real FPS
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
    main_cycle(wnd_sdl.get(), ctx_opengl.get(), wnd_cfg);

    return 0;
}

#endif