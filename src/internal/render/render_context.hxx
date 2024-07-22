#pragma once

#include "base_types.hxx"
#include "render/types.hxx"

namespace yg::render
{

/// @brief Parent class for any render api realization (Vulkan, OpenGL, Metal,
/// etc.) If you create new child class, you should set api
class context
{
public:
    enum [[nodiscard]] result_code
    {
        SUCCESS,
        ERROR
    };
    enum api
    {
        OpenGL,
        // Vulkan
    };

    virtual result_code initialize(const window_config& config)            = 0;
    virtual result_code render_triangle(const triangle<vertex2d_rgba>& tr) = 0;

    api get_api() const noexcept { return current_api; };

protected:
    api current_api;
};
} // namespace yg::render