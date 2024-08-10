#include "window_sdl.hxx"

#include "render/opengl/render_context_opengl.hxx"

#include "glad/glad.h"
#include "libassert/assert.hpp"
#include "spdlog/spdlog.h"
#include "vulkan/vulkan.h"

#include <SDL3/SDL.h>

yg::window_sdl::window_sdl(yg::render::context::api render_api) noexcept
{
    api = window_api::SDL;
    switch (render_api)
    {
        case yg::render::context::api::OpenGL:
            window_flags |= SDL_WINDOW_OPENGL;
            break;
    }
}

yg::window_sdl::~window_sdl() noexcept
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(static_cast<SDL_Window*>(wnd));
    SDL_Quit();
}

yg::window::result_code yg::window_sdl::initialize(window_config& config)
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

    if (config.is_full_screen)
    {
        window_flags |= SDL_WINDOW_FULLSCREEN;
        // TODO: Doesn't work on tile manager bspwm :D
        int temp_size_x, temp_size_y;
        SDL_GetWindowSize(
            static_cast<SDL_Window*>(wnd), &temp_size_x, &temp_size_y);
        spdlog::info(
            "Resize window from {}x{} to {}x{}, because window is fullscreen",
            config.size_x,
            config.size_y,
            temp_size_x,
            temp_size_y);
        config.size_x = temp_size_x;
        config.size_y = temp_size_y;
    }

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
    static bool      is_alive = true;
    static SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event))
    {
        switch (sdl_event.type)
        {
            case SDL_EVENT_QUIT:
                spdlog::info("SDL_EVENT_QUIT");
                is_alive = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                // clang-format off
                // if (SDLK_w == sdl_event.key.keysym.sym)     kb.w     = 1;
                // if (SDLK_s == sdl_event.key.keysym.sym)     kb.s     = 1;
                // if (SDLK_a == sdl_event.key.keysym.sym)     kb.a     = 1;
                // if (SDLK_d == sdl_event.key.keysym.sym)     kb.d     = 1;
                // if (SDLK_SPACE == sdl_event.key.keysym.sym) kb.space = 1;
                // if (SDLK_LEFT == sdl_event.key.keysym.sym)  kb.left  = 1;
                // if (SDLK_RIGHT == sdl_event.key.keysym.sym) kb.right = 1;
                // if (SDLK_UP == sdl_event.key.keysym.sym)    kb.up    = 1;
                // if (SDLK_DOWN == sdl_event.key.keysym.sym)  kb.down  = 1;
                // clang-format on
                break;

            case SDL_EVENT_KEY_UP:
                // clang-format off
                // if (SDLK_w == sdl_event.key.keysym.sym)     kb.w     = 0;
                // if (SDLK_s == sdl_event.key.keysym.sym)     kb.s     = 0;
                // if (SDLK_a == sdl_event.key.keysym.sym)     kb.a     = 0;
                // if (SDLK_d == sdl_event.key.keysym.sym)     kb.d     = 0;
                // if (SDLK_SPACE == sdl_event.key.keysym.sym) kb.space = 0;
                // if (SDLK_LEFT == sdl_event.key.keysym.sym)  kb.left  = 0;
                // if (SDLK_RIGHT == sdl_event.key.keysym.sym) kb.right = 0;
                // if (SDLK_UP == sdl_event.key.keysym.sym)    kb.up    = 0;
                // if (SDLK_DOWN == sdl_event.key.keysym.sym)  kb.down  = 0;
                // clang-format on
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                int temp_size_x, temp_size_y;
                SDL_GetWindowSize(
                    static_cast<SDL_Window*>(wnd), &temp_size_x, &temp_size_y);
                for (auto callback : to_resize)
                {
                    callback(temp_size_x, temp_size_y);
                }
                break;
        }
    }
    return is_alive;
}

void yg::window_sdl::swap_buffers()
{
    SDL_GL_SwapWindow(static_cast<SDL_Window*>(wnd));

    glClearColor(background_color.r,
                 background_color.g,
                 background_color.b,
                 background_color.a);
    YG_GL_CHECK_ERRORS()

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    YG_GL_CHECK_ERRORS()
}

void yg::window_sdl::on_resize(
    std::function<void(std::size_t, std::size_t)> func)
{
    // if (find(to_resize.begin(), to_resize.end(), func) == to_resize.end())
    to_resize.push_back(func);
}

yg::window::result_code yg::window_sdl::capture_render_context(
    yg::render::context* ctx)
{
    switch (ctx->get_api())
    {
        case yg::render::context::api::OpenGL:
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