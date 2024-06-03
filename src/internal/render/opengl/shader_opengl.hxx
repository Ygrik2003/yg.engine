#pragma once

#include "render/opengl/compiled_shader_opengl.hxx"
#include "render/shader.hxx"

namespace yg
{
class shader_opengl : public shader
{
public:
    shader_opengl();
    ~shader_opengl();

    void use() const override;
    void reload() override;
    void add_compiled_shader(const compiled_shader& shader) override;

    // TODO: Maybe need move to shader, if it abstract
    [[nodiscard]] std::int32_t link();

    void set_uniform1(const char* name, std::int32_t value) override;
    void set_uniform1(const char* name, std::uint32_t value) override;
    void set_uniform1(const char* name, float value) override;

    void set_uniform1v(const char*   name,
                       std::int32_t* value,
                       std::uint32_t count) override;
    void set_uniform1v(const char*    name,
                       std::uint32_t* value,
                       std::uint32_t  count) override;
    void set_uniform1v(const char*   name,
                       float*        value,
                       std::uint32_t count) override;

    void set_uniform2(const char*  name,
                      std::int32_t val1,
                      std::int32_t val2) override;
    void set_uniform2(const char*   name,
                      std::uint32_t val1,
                      std::uint32_t val2) override;
    void set_uniform2(const char* name, float val1, float val2) override;

    void set_uniform2v(const char*   name,
                       std::int32_t* val1,
                       std::int32_t* val2,
                       std::uint32_t count) override;
    void set_uniform2v(const char*    name,
                       std::uint32_t* val1,
                       std::uint32_t* val2,
                       std::uint32_t  count) override;
    void set_uniform2v(const char*   name,
                       float*        val1,
                       float*        val2,
                       std::uint32_t count) override;

    void set_uniform3(const char*  name,
                      std::int32_t val1,
                      std::int32_t val2,
                      std::int32_t val3) override;
    void set_uniform3(const char*   name,
                      std::uint32_t val1,
                      std::uint32_t val2,
                      std::uint32_t val3) override;
    void set_uniform3(const char* name,
                      float       val1,
                      float       val2,
                      float       val3) override;

    void set_uniform3v(const char*   name,
                       std::int32_t* val1,
                       std::int32_t* val2,
                       std::int32_t* val3,
                       std::uint32_t count) override;
    void set_uniform3v(const char*    name,
                       std::uint32_t* val1,
                       std::uint32_t* val2,
                       std::uint32_t* val3,
                       std::uint32_t  count) override;
    void set_uniform3v(const char*   name,
                       float*        val1,
                       float*        val2,
                       float*        val3,
                       std::uint32_t count) override;

    void set_uniform4(const char*  name,
                      std::int32_t val1,
                      std::int32_t val2,
                      std::int32_t val3,
                      std::int32_t val4) override;
    void set_uniform4(const char*   name,
                      std::uint32_t val1,
                      std::uint32_t val2,
                      std::uint32_t val3,
                      std::uint32_t val4) override;
    void set_uniform4(const char* name,
                      float       val1,
                      float       val2,
                      float       val3,
                      float       val4) override;

    void set_uniform4v(const char*   name,
                       std::int32_t* val1,
                       std::int32_t* val2,
                       std::int32_t* val3,
                       std::int32_t* val4,
                       std::uint32_t count) override;
    void set_uniform4v(const char*    name,
                       std::uint32_t* val1,
                       std::uint32_t* val2,
                       std::uint32_t* val3,
                       std::uint32_t* val4,
                       std::uint32_t  count) override;
    void set_uniform4v(const char*   name,
                       float*        val1,
                       float*        val2,
                       float*        val3,
                       float*        val4,
                       std::uint32_t count) override;
};
} // namespace yg