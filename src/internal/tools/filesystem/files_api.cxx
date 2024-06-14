#include "files_api.hxx"
#include "libassert/assert.hpp"

// TODO: Make it crossplatform
std::string yg::read_file(const char* path)
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