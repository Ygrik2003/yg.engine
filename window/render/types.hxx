#include "glm/glm.hpp"

#include <array>

namespace yg
{
class vertex3d
{
public:
    vertex3d(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3)
        : values{ vert1, vert2, vert3 }
    {
    }
    inline const glm::vec3* data() const noexcept { return values.data(); }

private:
    std::array<glm::vec3, 3> values;
};

} // namespace yg