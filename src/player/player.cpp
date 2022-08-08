#include "player.hpp"
#include <raylib.h>

Player::Player(Vector2 pos, Vector2 size) {
    this->pos = pos;
    this->size = size;
}

void Player::draw() {
    DrawRectangleV(
        this->pos,
        this->size,
        GRAY
    );
}

void Player::update() {
    //this->apply_gravity();
    this->handle_inputs();
}

void Player::handle_inputs() {
    if (IsKeyDown(KEY_A)) {
        this->pos.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        this->pos.x += 1;
    }

    if (IsKeyDown(KEY_SPACE)) {
        this->vel.y = -1.0f;
    }
}

void Player::apply_gravity() {
    if (
        !this->inFloor &&
        this->vel.y <= 1.8f
    ) {
        this->vel.y += 0.01f;
    }

    this->pos.y += this->vel.y;
}
