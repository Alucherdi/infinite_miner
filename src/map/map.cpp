#include "map.hpp"
#include <raylib.h>
#include "../config/setup.hpp"
#include "../physics/collision.hpp"

Map::Map() {
    this->hInit = SCREEN_HEIGHT / 2;
    this->wInit = 0;
    this->map.push_back(Rectangle {
        -10.0f, 30.0f, 100.0f, 30.0f
    });
}

void Map::draw() {
    for (int i = 0; i < this->map.size(); i++) {
        DrawRectangleRec(this->map[i], BLUE);
    }
}

void Map::draw_block(int x, int y, int w, int h, bool c) {
    DrawRectangle(
        x, y, w, h,
        c ? MAROON : RED
    );
}
