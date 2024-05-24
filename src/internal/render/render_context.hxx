#pragma once

namespace yg
{

/// @brief Parent class for any render api realization (Vulkan, OpenGL, Metal,
/// etc.) If you create new child class, you should set render_api
class render_context
{
public:
    enum [[nodiscard]] result_code
    {
        SUCCESS,
        ERROR
    };
    enum render_api
    {
        OpenGL,
        Vulkan
    };

    virtual result_code initialize()      = 0;
    virtual result_code render_triangle() = 0;

    render_api get_api() const noexcept { return api; };

protected:
    render_api api;
};
} // namespace yg