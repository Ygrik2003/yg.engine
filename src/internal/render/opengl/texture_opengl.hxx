#include "render/texture.hxx"

#include <string>

namespace yg::render::opengl
{
class texture_impl : public texture
{
public:
    explicit texture_impl(std::string path_to_png);

    explicit texture_impl(const void* pixels,
                          std::size_t width,
                          std::size_t height);

    void bind() const noexcept override;

private:
    void gen_texture_from_pixels(std::int32_t mipmap_level = 0,
                                 std::int32_t border       = 0) override;
};
} // namespace yg::render::opengl