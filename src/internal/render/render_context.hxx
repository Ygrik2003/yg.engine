#pragma once

namespace yg
{

/// @brief Parrent class for any render api realization (Vulkan, OpenGL, Metal,
/// etc.) If you create new child class, you shoud set redner_api
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