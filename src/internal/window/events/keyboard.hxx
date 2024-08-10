#pragma once

#include <cstdint>

namespace events
{
// struct event_mouse
// {
//     uint8_t left_clicked : 1;
//     uint8_t left_released : 1;
//     uint8_t right_clicked : 1;
//     uint8_t right_released : 1;
//     uint8_t center_clicked : 1;
//     uint8_t center_released : 1;
//     uint8_t back_clicked : 1;
//     uint8_t back_released : 1;
//     uint8_t next_clicked : 1;
//     uint8_t next_released : 1;
// } mouse;

// struct event_motion
// {
//     float x;
//     float y;
//     float x_rel;
//     float y_rel;
// } motion;

struct keyboard
{
    uint8_t w : 1;
    uint8_t s : 1;
    uint8_t a : 1;
    uint8_t d : 1;
    uint8_t left : 1;
    uint8_t right : 1;
    uint8_t up : 1;
    uint8_t down : 1;
    uint8_t space : 1;
    uint8_t esc : 1;
};

// struct event_action
// {
//     uint8_t quit : 1;
//     uint8_t resize : 1;
//     uint8_t skip : 1;

// } action;

// void clear()
// {
//     mouse    = event_mouse{};
//     motion   = event_motion{};
//     keyboard = event_keyboard{};
//     action   = event_action{};
// }
}; // namespace events
