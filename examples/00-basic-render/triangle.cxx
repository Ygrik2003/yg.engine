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
    using namespace yg;
    window_config wnd_cfg;
    // wnd_cfg.size_x = 600;
    // wnd_cfg.size_y = 600;

    window*          wnd_sdl    = new window_sdl(render::context::api::OpenGL);
    render::context* ctx_opengl = new render::opengl::context_impl();

    auto wnd_manager = new window_manager(wnd_cfg, wnd_sdl, ctx_opengl);

    auto* shader_opengl_vert = new render::opengl::compiled_shader_impl(
        "data/shaders/shader.vert", render::shader_type::VERTEX);
    auto* shader_opengl_frag = new render::opengl::compiled_shader_impl(
        "data/shaders/shader.frag", render::shader_type::FRAGMENT);

    auto shader_opengl = render::opengl::shader_impl();
    shader_opengl.add_compiled_shader(shader_opengl_vert);
    shader_opengl.add_compiled_shader(shader_opengl_frag);

    shader_opengl.use();

    render::triangle<render::vertex2d_rgba> test_tr{
        { { 0., -1. }, 0xFF0000FF },
        { { 1., 1. }, 0xFFFF0000 },
        { { -1., 1. }, 0xFF00FF00 }
    };

    while (wnd_sdl->process_events())
    {
        using namespace std::chrono;
        using namespace std::this_thread;
        auto result = ctx_opengl->render_triangle(test_tr);
        wnd_sdl->swap_buffers();
        sleep_for(milliseconds(1000 / wnd_cfg.fps)); // TODO: do real FPS
    }
    return 0;
}