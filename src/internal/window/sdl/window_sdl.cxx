#include "window_sdl.hxx"

#include "libassert/assert.hpp"
#include "spdlog/spdlog.h"

#include <SDL3/SDL.h>

#include "glad/glad.h"
#include "vulkan/vulkan.h"

yg::window_sdl::window_sdl(render_context::render_api render_api) noexcept
{
    api = window_api::SDL;
    switch (render_api)
    {
        case render_context::render_api::OpenGL:
            window_flags |= SDL_WINDOW_OPENGL;
            break;
    }
}

yg::window::result_code yg::window_sdl::initialize(const window_config& config)
{
    int err_code;

    err_code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    if (err_code)
    {
        spdlog::critical("Can't init SDL with error: {}", SDL_GetError());
        SDL_Quit();
        return result_code::ERROR;
    }

    wnd = SDL_CreateWindow(
        config.name, config.size_x, config.size_y, window_flags);

    if (!wnd)
    {
        spdlog::critical("Can't create SDL Window with error: {}",
                         SDL_GetError());
        SDL_Quit();
        return result_code::ERROR;
    }

    return result_code::SUCCESS;
}

bool yg::window_sdl::process_events()
{
    bool      is_alive = true;
    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event))
    {
        switch (sdl_event.type)
        {
            case SDL_EVENT_QUIT:
                is_alive = false;
                break;
        }
    }
    return is_alive;
}

void yg::window_sdl::swap_buffers()
{
    SDL_GL_SwapWindow(static_cast<SDL_Window*>(wnd));

    glClearColor(77. / 255., 143. / 255., 210. / 255., 1.);
    YG_GL_CHECK_ERRORS()

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    YG_GL_CHECK_ERRORS()
}

yg::window::result_code yg::window_sdl::capture_render_context(
    render_context* ctx)
{
    switch (ctx->get_api())
    {
        case render_context::render_api::OpenGL:
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                                SDL_GL_CONTEXT_PROFILE_ES);
            gl_context = SDL_GL_CreateContext(static_cast<SDL_Window*>(wnd));
            if (gl_context == nullptr)
            {
                spdlog::critical(SDL_GetError());
                SDL_Quit();
                return result_code::ERROR;
            }
            auto load_gl_func = [](const char* name)
            {
                SDL_FunctionPointer gl_pointer = SDL_GL_GetProcAddress(name);
                assert(gl_pointer != nullptr && "can't load GL function");

                return reinterpret_cast<void*>(gl_pointer);
            };
            if (gladLoadGLES2Loader(load_gl_func) == 0)
            {
                spdlog::critical("cant init glad");
                SDL_Quit();
                return result_code::ERROR;
            }
            break;
    }

    return result_code::SUCCESS;
}
