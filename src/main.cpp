#include <memory>
#include <raylib.h>

#include "config/setup.hpp"
#include "map/map.hpp"

int main() {
    InitWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SCREEN_TITLE
    );

    Vector2 ballPosition = {
        (float) SCREEN_WIDTH / 2,
        (float) SCREEN_HEIGHT / 2
    };

    Map map{};

    while (!WindowShouldClose()) {
        BeginDrawing();
        map.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
