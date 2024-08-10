#include "files_api.hxx"

#include "libassert/assert.hpp"
#include "picopng/picopng.hxx"
#include "spdlog/spdlog.h"

// TODO: Make it cross-platform with SDL_...
// TODO: think about ASSERT and exceptions
std::string yg::files_api::read_file(const char* path)
{
    constexpr auto read_size = std::size_t(4096);
    auto           stream    = std::ifstream(path);
    stream.exceptions(std::ios_base::badbit);

    ASSERT(stream && "file does not exist");

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size))
    {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

// TODO: think about ASSERT and exceptions
void yg::files_api::get_pixels_from_png(const char*             path,
                                        std::vector<std::byte>& image,
                                        unsigned long&          w,
                                        unsigned long&          h)
{
    std::vector<std::byte> png_file_in_memory;
    std::string            file = read_file(path);
    png_file_in_memory.resize(file.size());

    std::copy(reinterpret_cast<std::byte*>(file.data()),
              reinterpret_cast<std::byte*>(file.data() + file.size()),
              png_file_in_memory.begin());

    int error = decodePNG(
        image, w, h, &png_file_in_memory[0], png_file_in_memory.size(), true);

    if (error != 0)
    {
        spdlog::error("error: {}", error);
        throw std::runtime_error("can't load texture");
    }
}
