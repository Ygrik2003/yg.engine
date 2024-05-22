#include "forwards.hxx"

class damage_entity
{
public:
    uint8_t get_damage() const noexcept { return damage; }

protected:
    uint8_t damage = 3;
};