#include <cstdint>
#include <iostream>

class damage_entity;
class player;
class bot;

class damage_entity
{
public:
    uint8_t get_damage() const noexcept { return damage; }

protected:
    uint8_t damage = 3;
};

class bot : public damage_entity
{
public:
    void recive_damage(const player& enemy_bot) noexcept;

protected:
    uint8_t hp = 10;
};

class player : public damage_entity
{
public:
    void recive_damage(const bot& enemy_bot) noexcept;

protected:
    const uint8_t damage = 1;
    uint8_t       hp     = 10;
};

void bot::recive_damage(const player& enemy_player) noexcept
{
    if (hp >= enemy_player.get_damage())
    {

        hp -= enemy_player.get_damage();
    }
    else
    {
        hp = 0;
    }
    std::cout << "Bot gave " << static_cast<int>(enemy_player.get_damage())
              << " damage from Player. Current HP: " << static_cast<int>(hp)
              << std::endl;
}

void player::recive_damage(const bot& enemy_bot) noexcept
{
    if (hp >= enemy_bot.get_damage())
    {

        hp -= enemy_bot.get_damage();
    }
    else
    {
        hp = 0;
    }
    std::cout << "Player gave " << static_cast<int>(enemy_bot.get_damage())
              << " damage from Bot. Current HP: " << static_cast<int>(hp)
              << std::endl;
}

int main()
{
    bot    b1;
    player p1;

    b1.recive_damage(p1);
    p1.recive_damage(b1);
    p1.recive_damage(b1);
    p1.recive_damage(b1);
    p1.recive_damage(b1);

    return EXIT_SUCCESS;
}