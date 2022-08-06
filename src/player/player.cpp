#include "player.hpp"
#include <raylib.h>

Player::Player(Vector2 pos, Vector2 size) {
    this->pos = pos;
    this->size = size;
}

void Player::draw() {
    DrawRectangle(
        this->pos.x, this->pos.y,
        this->size.x, this->size.y,
        GRAY
    );
}

void Player::update() {
    if (IsKeyDown(KEY_A)) {
        this->pos.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        this->pos.x += 1;
    }
}
