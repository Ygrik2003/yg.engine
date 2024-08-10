#include "render/types.hxx"

namespace yg::render
{
class texture
{
public:
    virtual void bind() const noexcept = 0;

protected:
    virtual void  gen_texture_from_pixels(std::int32_t mipmap_level,
                                          std::int32_t border) = 0;
    std::uint32_t handle{};
    std::size_t   width{};
    std::size_t   height{};
    const void*   pixels = nullptr;
};
} // namespace yg::render