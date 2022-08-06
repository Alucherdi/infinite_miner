#include <memory>
#include <raylib.h>

#include "config/setup.hpp"
#include "map/map.hpp"
#include "player/player.hpp"

int main() {
    InitWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SCREEN_TITLE
    );


    Player player(Vector2{ 0, 100 }, Vector2{ 8, 8 });
    Map map{};

    Camera2D camera = { 0 };
    camera.target = player.pos;
    camera.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        player.update();
        camera.target = player.pos;

        ClearBackground(WHITE);

        BeginMode2D(camera);
            map.draw();
            player.draw();
        EndMode2D();

        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
