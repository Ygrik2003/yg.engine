#include "base_types.hxx"
#include "render/opengl/compiled_shader_opengl.hxx"
#include "render/opengl/render_context_opengl.hxx"
#include "render/opengl/shader_opengl.hxx"
#include "window/sdl/window_sdl.hxx"
#include "window/window_manager.hxx"

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

    auto* shader_opengl_vert = new yg::compiled_shader_opengl(
        "data/shaders/shader.vert", yg::shader_type::VERTEX);
    auto* shader_opengl_frag = new yg::compiled_shader_opengl(
        "data/shaders/shader.frag", yg::shader_type::FRAGMENT);

    auto shader_opengl = yg::shader_opengl();
    shader_opengl.add_compiled_shader(shader_opengl_vert);
    shader_opengl.add_compiled_shader(shader_opengl_frag);

    yg::triangle<yg::vertex2d_rgba> test_tr{ { { 0., -1. }, 0u },
                                             { { 1., 1. }, 1u << 16 },
                                             { { -1., 1. }, 1u << 31 } };

    while (wnd_sdl->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;
        auto result = ctx_opengl->render_triangle(test_tr);
        wnd_sdl->swap_buffers();
        sleep_for(milliseconds(1000 / wnd_cfg.fps));
    }
    return 0;
}