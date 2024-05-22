#include "window/render/render_context.hxx"

namespace yg
{
class render_context_opengl : public render_context
{
public:
    render_context_opengl() noexcept { api = render_api::OpenGL; }
    ~render_context_opengl() noexcept                        = default;
    render_context_opengl(const render_context_opengl& ctx)  = delete;
    render_context_opengl(const render_context_opengl&& ctx) = delete;

    result_code initialize() override;
    result_code render_triangle() override;
};
} // namespace yg