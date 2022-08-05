#include "map.hpp"
#include <raylib.h>
#include "../config/setup.hpp"

Map::Map() {
    this->hInit = SCREEN_HEIGHT / 2;
    this->wInit = 0;
}

void Map::draw() {
    for (int x = 0; x < SCREEN_WIDTH / this->bw; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / this->bh; y++) {
            this->draw_block(
                this->wInit + x * 10,
                this->hInit + y * 10,
                this->bw, this->bh
            );
        }
    }
}

void Map::draw_block(int x, int y, int w, int h) {
    DrawRectangle(
        x, y, w, h,
        MAROON
    );
}
