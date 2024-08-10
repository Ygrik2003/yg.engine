#include "base_types.hxx"
#include "render/opengl/compiled_shader_opengl.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "render/opengl/shader_opengl.hxx"
#include "render/opengl/texture_opengl.hxx"
#include "window/events/keyboard.hxx"
#include "window/sdl/window_sdl.hxx"
#include "window/window_manager.hxx"

#include "spdlog/spdlog.h"

#include <chrono>
#include <thread>

enum triangle_type
{
    contour,
    textured,
    colored,
    textured_colored,

};

int main()
{
    using namespace yg;
    window_config wnd_cfg;
    // wnd_cfg.size_x = 600;
    // wnd_cfg.size_y = 600;

    window*          wnd_sdl    = new window_sdl(render::context::api::OpenGL);
    render::context* ctx_opengl = new render::opengl::context_impl();

    auto wnd_manager = new window_manager(wnd_cfg, wnd_sdl, ctx_opengl);

    auto* shader_opengl_vert = new render::opengl::compiled_shader_impl(
        "data/shaders/basic_shader.vert", render::shader_type::VERTEX);
    auto* shader_opengl_frag = new render::opengl::compiled_shader_impl(
        "data/shaders/basic_shader.frag", render::shader_type::FRAGMENT);

    auto shader_opengl = render::opengl::shader_impl();
    shader_opengl.add_compiled_shader(shader_opengl_vert);
    shader_opengl.add_compiled_shader(shader_opengl_frag);

    shader_opengl.use();

    render::opengl::texture_impl texture_tr("data/test_texture.png");

    texture_tr.bind();

    render::triangle<render::vertex2d>      test_tr{ { { 0., -1. } },
                                                     { { 1., 1. } },
                                                     { { -1., 1. } } };
    render::triangle<render::vertex2d_rgba> test_tr_rgba{
        { { 0., -1. }, 0xFF0000FF },
        { { 1., 1. }, 0xFFFF0000 },
        { { -1., 1. }, 0xFF00FF00 }
    };

    render::triangle<render::vertex2d_uv> test_tr_uv{
        { { 0., -1. }, { 0., 1. } },
        { { 1., 1. }, { 1., 1. } },
        { { -1., 1. }, { 1., 0. } }
    };
    render::triangle<render::vertex2d_uv_rgba> test_tr_uv_rgba{
        { { 0., -1. }, { 0., 1. }, 0xFF0000FF },
        { { 1., 1. }, { -1., -1. }, 0xFFFF0000 },
        { { -1., 1. }, { 1., -1. }, 0xFF00FF00 }
    };

    triangle_type current_tr = triangle_type::textured;
    // std::thread(
    //     [&current_tr]()
    //     {
    //         while (true)
    //         {
    //             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //             current_tr = static_cast<triangle_type>(
    //                 (static_cast<int>(current_tr) + 1) %
    //                 sizeof(triangle_type));
    //             spdlog::info("Toggled render type of triangles to {}",
    //                          static_cast<int>(current_tr));
    //         }
    //     })
    //     .detach();

    render::context::result_code result;
    while (wnd_sdl->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;

        switch (current_tr)
        {
            case triangle_type::contour:
                result = ctx_opengl->render_triangle(test_tr);
                break;
            case triangle_type::colored:
                result = ctx_opengl->render_triangle(test_tr_rgba);
                break;
            case triangle_type::textured:
                result = ctx_opengl->render_triangle(test_tr_uv);
                break;
            case triangle_type::textured_colored:
                result = ctx_opengl->render_triangle(test_tr_uv_rgba);
                break;
        }
        if (render::context::result_code::ERROR == result)
        {
            spdlog::error("Cant render triangle triangle_type(%d)",
                          static_cast<int>(current_tr));
        }
        wnd_sdl->swap_buffers();
        sleep_for(milliseconds(1000 / wnd_cfg.fps)); // TODO: do real FPS
    }
    return 0;
}