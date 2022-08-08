#include "map.hpp"
#include <raylib.h>
#include "../config/setup.hpp"
#include "../physics/collision.hpp"

Map::Map() {
    this->hInit = SCREEN_HEIGHT / 2;
    this->wInit = 0;
}

void Map::draw() {
    /*for (int x = 0; x < SCREEN_WIDTH / this->bw; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / this->bh; y++) {
            this->draw_block(
                this->wInit + x * 10,
                this->hInit + y * 10,
                this->bw, this->bh
            );
        }
    }*/
    Vector2 origin { 0.0f, 0.0f };
    Vector2 direction = GetMousePosition(); 

    DrawLineV(origin, direction, GREEN);

    Vector2 cp, cn;

    Rectangle r {100.0f, 100.0f, 200.0f, 200.0f };

    float t;


    bool colliding = Collision::check(
        origin, direction, r, cp, cn, t
    );

    this->draw_block(100, 100, 200, 200, colliding && t <= 1.0f);
    if (colliding && t <= 1.0f) {
        DrawCircleV(cp, 6.0f, DARKBLUE);
        DrawLineV(cp, (Vector2) {
            cp.x + (cn.x * 50),
            cp.y + (cn.y * 50),
        }, DARKBROWN);
    }
}

void Map::draw_block(int x, int y, int w, int h, bool c) {
    DrawRectangle(
        x, y, w, h,
        c ? MAROON : RED
    );
}
