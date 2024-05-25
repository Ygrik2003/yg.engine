#pragma once

#include <cstdint>

namespace yg
{
#pragma pack(push, 8)
struct window_config
{
    const char* name = "Tanchiki";

    std::uint16_t size_x;
    std::uint16_t size_y;

    bool is_full_screen;
    bool is_resizeble;

    const std::uint8_t fps = 60;
};
#pragma pack(pop)

} // namespace yg