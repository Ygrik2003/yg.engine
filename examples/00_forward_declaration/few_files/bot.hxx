#include "forwards.hxx"

class bot : public damage_entity
{
public:
    void recive_damage(const player& enemy_bot) noexcept;

protected:
    uint8_t hp = 10;
};