#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>

#include "config/setup.hpp"
#include "map/map.hpp"
#include "physics/collision.hpp"
#include "player/player.hpp"

int main() {
    InitWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SCREEN_TITLE
    );


    Player player(Vector2{ 0, 0 }, Vector2{ 30.0f, 30.0f });
    Map map{};

    std::string iscol = "";
    Camera2D camera = { 0 };
    camera.target = player.pos;
    camera.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        float dt = 1.0f / GetFPS();
        ClearBackground(WHITE);

        player.update();

        Vector2 cp, cn;
        float ct;
        for (int i = 0; i < map.map.size(); i++) {
            if (
                Collision::check(
                    (Rectangle) {
                        player.pos.x, player.pos.y,
                        player.size.x, player.size.y
                    },
                    map.map[i],
                    player.vel,
                    cp, cn, ct, dt
                )
            ) {
                player.vel = (Vector2) {
                    cn.x * std::abs(player.vel.x) * (1 - ct),
                    cn.y * std::abs(player.vel.y) * (1 - ct)
                };
            }
        }

        player.pos = (Vector2) {
            player.pos.x + player.vel.x,
            player.pos.y + player.vel.y
        };

        camera.target = player.pos;
        BeginMode2D(camera);
            map.draw();
            player.draw();
        EndMode2D();

        BeginDrawing();
            DrawText(TextFormat("%02.02f", dt), 0, 0, 8, BLACK);
            DrawText(TextFormat("player.pos: %02.02f, %02.02f", player.pos.x, player.pos.y), 0, 10, 8, BLACK);
            DrawText(TextFormat("player.vel: %02.02f, %02.02f", player.vel.x, player.vel.y), 0, 20, 8, BLACK);
            DrawText(TextFormat("contact_normal: %02.02f, %02.02f", cn.x, cn.y), 0, 30, 8, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
