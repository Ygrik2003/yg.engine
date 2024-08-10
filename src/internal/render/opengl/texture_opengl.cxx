#include "texture_opengl.hxx"

#include "tools/filesystem/files_api.hxx"

#include "glad/glad.h"

namespace yg::render::opengl
{
texture_impl::texture_impl(std::string path_to_png)
{
    std::vector<std::byte> pixels_result;
    files_api::get_pixels_from_png(
        path_to_png.c_str(), pixels_result, width, height);
    pixels = static_cast<void*>(pixels_result.data());
    gen_texture_from_pixels();
}
texture_impl::texture_impl(const void* pixels,
                           std::size_t width,
                           std::size_t height)
{
    this->pixels = pixels;
    this->width  = width;
    this->height = height;
    gen_texture_from_pixels();
}
void texture_impl::bind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, handle);
    YG_GL_CHECK_ERRORS();
}
void texture_impl::gen_texture_from_pixels(std::int32_t mipmap_level,
                                           std::int32_t border)
{
    glGenTextures(1, &handle);
    YG_GL_CHECK_ERRORS();
    glBindTexture(GL_TEXTURE_2D, handle);
    YG_GL_CHECK_ERRORS();

    glTexImage2D(GL_TEXTURE_2D,
                 static_cast<GLint>(mipmap_level),
                 GL_RGBA,
                 static_cast<GLsizei>(width),
                 static_cast<GLsizei>(height),
                 static_cast<GLint>(border),
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 pixels);
    YG_GL_CHECK_ERRORS();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    YG_GL_CHECK_ERRORS();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    YG_GL_CHECK_ERRORS();
}
} // namespace yg::render::opengl