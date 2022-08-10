#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>

#include "config/setup.hpp"
#include "map/map.hpp"
#include "physics/collision.hpp"
#include "physics/rigidbody.hpp"
#include "player/player.hpp"

int main() {
    InitWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SCREEN_TITLE
    );

    struct {
        RigidBody rb{};
    } player;

    player.rb.body = (Rectangle) {
        0.0f, 0.0f, 20.0f, 20.0f
    };

    player.rb.vel = (Vector2) {
        0.0f, 0.0f
    };

    struct {
        RigidBody rb{};
    } block;

    block.rb.body = (Rectangle) {
        100.0f, 100.0f, 30.0f, 30.0f
    };

    std::string iscol = "";
    Camera2D camera = { 0 };
    camera.target = (Vector2) { player.rb.body.x , player.rb.body.y };
    camera.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        ClearBackground(WHITE);

        if (
            IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_D)
        ) {
            player.rb.vel.x = IsKeyDown(KEY_A) ? -100.0f : 100.0f;
        } else {
            player.rb.vel.x = 0.0f;
        }

        if (
            IsKeyPressed(KEY_SPACE)
        ) {
            player.rb.vel.y = -500.0f;
        }

        if (player.rb.vel.y < 100.0f) player.rb.vel.y += 5.0f;

        Collision::resolve_dynamic_ray_collision(
            &player.rb,
            &block.rb,
            dt
        );

        BeginDrawing();

            BeginMode2D(camera);
                DrawRectangleRec(block.rb.body, BLUE);
                DrawRectangleRec(player.rb.body, RED);
            EndMode2D();

            DrawText(TextFormat("%02.02f", dt), 0, 0, 8, BLACK);
            DrawText(TextFormat("player.pos: %02.02f, %02.02f", player.rb.body.x, player.rb.body.y), 0, 10, 8, BLACK);
            DrawText(TextFormat("player.vel: %02.02f, %02.02f", player.rb.vel.x, player.rb.vel.y), 0, 20, 8, BLACK);
        EndDrawing();

        player.rb.body.x += player.rb.vel.x * dt;
        player.rb.body.y += player.rb.vel.y * dt;

        camera.target = (Vector2) { player.rb.body.x , player.rb.body.y };
    }

    CloseWindow();
    return 0;
}
