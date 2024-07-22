#include "render/render_context.hxx"

namespace yg::render
{
namespace opengl
{
class context_impl : public context
{
public:
    context_impl() noexcept { current_api = api::OpenGL; }
    ~context_impl() noexcept               = default;
    context_impl(const context_impl& ctx)  = delete;
    context_impl(const context_impl&& ctx) = delete;

    result_code initialize(const window_config& config) override;
    result_code render_triangle(const triangle<vertex2d_rgba>& tr) override;
};
} // namespace opengl
} // namespace yg::render