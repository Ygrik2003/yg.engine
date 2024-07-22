#include "render/types.hxx"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Test triangle with 2d vertex types", "[single-file]")
{
    using namespace yg::render;

    triangle<vertex2d> trv2d{ { { 1.f, 1.f } },
                              { { 0.f, 0.f } },
                              { { 0.f, 1.f } } };
    CHECK(trv2d.size() == 3 * 2 * sizeof(float));

    triangle<vertex2d_rgba> trv2d_rgba{ { { 1.f, 1.f }, 0xFFFFFFFF },
                                        { { 0.f, 0.f }, 0xFFFFFFFF },
                                        { { 0.f, 1.f }, 0xFFFFFFFF } };
    CHECK(trv2d_rgba.size() == 3 * (2 * sizeof(float) + sizeof(std::uint32_t)));

    triangle<vertex2d_uv> trv2d_uv{ { { 1.f, 1.f }, { 0.f, 0.f } },
                                    { { 0.f, 0.f }, { 1.f, 0.f } },
                                    { { 0.f, 1.f }, { 1.f, 1.f } } };
    CHECK(trv2d_uv.size() == 3 * (2 * sizeof(float) + 2 * sizeof(float)));

    triangle<vertex2d_uv_rgba> trv2d_uv_rgba{
        { { 1.f, 1.f }, { 0.f, 0.f }, 0xFFFFFFFF },
        { { 0.f, 0.f }, { 1.f, 0.f }, 0xFFFFFFFF },
        { { 0.f, 1.f }, { 1.f, 1.f }, 0xFFFFFFFF }
    };
    CHECK(trv2d_uv_rgba.size() ==
          3 * (2 * sizeof(float) + 2 * sizeof(float) + sizeof(std::uint32_t)));
}
TEST_CASE("Test triangle with 3d vertex types", "[single-file]")
{
    using namespace yg::render;

    triangle<vertex3d> trv3d{ { { 1.f, 1.f, 1.f } },
                              { { 0.f, 0.f, 0.f } },
                              { { 0.f, 1.f, 0.5f } } };
    CHECK(trv3d.size() == 3 * 3 * sizeof(float));

    triangle<vertex3d_rgba> trv3d_rgba{ { { 1.f, 1.f, 1.f }, 0xFFFFFFFF },
                                        { { 0.f, 0.f, 0.f }, 0xFFFFFFFF },
                                        { { 0.f, 1.f, 0.5f }, 0xFFFFFFFF } };
    CHECK(trv3d_rgba.size() == 3 * (3 * sizeof(float) + sizeof(std::uint32_t)));

    triangle<vertex3d_uv> trv3d_uv{ { { 1.f, 1.f, 1.f }, { 0.f, 0.f } },
                                    { { 0.f, 0.f, 0.f }, { 1.f, 0.f } },
                                    { { 0.f, 1.f, 0.5f }, { 1.f, 1.f } } };
    CHECK(trv3d_uv.size() == 3 * (3 * sizeof(float) + 2 * sizeof(float)));

    triangle<vertex3d_uv_rgba> trv3d_uv_rgba{
        { { 1.f, 1.f, 1.f }, { 0.f, 0.f }, 0xFFFFFFFF },
        { { 0.f, 0.f, 0.f }, { 1.f, 0.f }, 0xFFFFFFFF },
        { { 0.f, 1.f, 0.5f }, { 1.f, 1.f }, 0xFFFFFFFF }
    };
    CHECK(trv3d_uv_rgba.size() ==
          3 * (3 * sizeof(float) + 2 * sizeof(float) + sizeof(std::uint32_t)));
}