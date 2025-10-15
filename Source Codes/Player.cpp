#include "player.hpp"

Player::Player(const char& color) : _color(color) {}

char Player::get_color() const {
    return _color;
}

