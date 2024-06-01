#pragma once

#include "render/compiled_shader.hxx"

#include <cstdint>

namespace yg
{

class shader
{
public:
    virtual void use() const                                        = 0;
    virtual void reload()                                           = 0;
    virtual void add_compiled_shader(const compiled_shader& shader) = 0;

    virtual void set_uniform1(const char* name, std::int32_t value)  = 0;
    virtual void set_uniform1(const char* name, std::uint32_t value) = 0;
    virtual void set_uniform1(const char* name, float value)         = 0;

    virtual void set_uniform1v(const char*   name,
                               std::int32_t* value,
                               std::uint32_t count) = 0;
    virtual void set_uniform1v(const char*    name,
                               std::uint32_t* value,
                               std::uint32_t  count) = 0;
    virtual void set_uniform1v(const char*   name,
                               float*        value,
                               std::uint32_t count) = 0;

    virtual void set_uniform2(const char*  name,
                              std::int32_t val1,
                              std::int32_t val2)                        = 0;
    virtual void set_uniform2(const char*   name,
                              std::uint32_t val1,
                              std::uint32_t val2)                       = 0;
    virtual void set_uniform2(const char* name, float val1, float val2) = 0;

    virtual void set_uniform2v(const char*   name,
                               std::int32_t* val1,
                               std::int32_t* val2,
                               std::uint32_t count) = 0;
    virtual void set_uniform2v(const char*    name,
                               std::uint32_t* val1,
                               std::uint32_t* val2,
                               std::uint32_t  count) = 0;
    virtual void set_uniform2v(const char*   name,
                               float*        val1,
                               float*        val2,
                               std::uint32_t count) = 0;

    virtual void set_uniform3(const char*  name,
                              std::int32_t val1,
                              std::int32_t val2,
                              std::int32_t val3)  = 0;
    virtual void set_uniform3(const char*   name,
                              std::uint32_t val1,
                              std::uint32_t val2,
                              std::uint32_t val3) = 0;
    virtual void set_uniform3(const char* name,
                              float       val1,
                              float       val2,
                              float       val3)         = 0;

    virtual void set_uniform3v(const char*   name,
                               std::int32_t* val1,
                               std::int32_t* val2,
                               std::int32_t* val3,
                               std::uint32_t count) = 0;
    virtual void set_uniform3v(const char*    name,
                               std::uint32_t* val1,
                               std::uint32_t* val2,
                               std::uint32_t* val3,
                               std::uint32_t  count) = 0;
    virtual void set_uniform3v(const char*   name,
                               float*        val1,
                               float*        val2,
                               float*        val3,
                               std::uint32_t count) = 0;

    virtual void set_uniform4(const char*  name,
                              std::int32_t val1,
                              std::int32_t val2,
                              std::int32_t val3,
                              std::int32_t val4)  = 0;
    virtual void set_uniform4(const char*   name,
                              std::uint32_t val1,
                              std::uint32_t val2,
                              std::uint32_t val3,
                              std::uint32_t val4) = 0;
    virtual void set_uniform4(
        const char* name, float val1, float val2, float val3, float val4) = 0;

    virtual void set_uniform4v(const char*   name,
                               std::int32_t* val1,
                               std::int32_t* val2,
                               std::int32_t* val3,
                               std::int32_t* val4,
                               std::uint32_t count) = 0;
    virtual void set_uniform4v(const char*    name,
                               std::uint32_t* val1,
                               std::uint32_t* val2,
                               std::uint32_t* val3,
                               std::uint32_t* val4,
                               std::uint32_t  count) = 0;
    virtual void set_uniform4v(const char*   name,
                               float*        val1,
                               float*        val2,
                               float*        val3,
                               float*        val4,
                               std::uint32_t count) = 0;

protected:
    std::uint32_t program;
};
} // namespace yg