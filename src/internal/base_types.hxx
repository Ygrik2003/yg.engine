#pragma once

#include <cstdint>

namespace yg
{
namespace constants
{
#ifdef YG_ENGINE_UNIT_TESTS
constexpr bool is_unit_tests_binary = true;
#else
constexpr bool is_unit_tests_binary = false;
#endif
} // namespace constants

#pragma pack(push, 8)
struct window_config
{
    const char* name = "Tanchiki";

    std::uint16_t size_x = 600;
    std::uint16_t size_y = 600;

    bool is_full_screen = true;
    bool is_resizable   = false;

    const std::uint8_t fps = 60;
};
#pragma pack(pop)

namespace color
{
struct rgba
{
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 1;
};
} // namespace color

} // namespace yg