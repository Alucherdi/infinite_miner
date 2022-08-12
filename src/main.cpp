#include <raylib.h>
#include <iostream>
#include <vector>

#include "physics/v2.hpp"
#include "physics/entity.hpp"
#include "physics/collision.hpp"

#include "config/setup.hpp"


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(144);

    float ac = 100.0f;
    float dt = 0.0f;
    float g = 40.0f;
    float jf = 800.0f;

    entity p({ 0.0f, 0.0f }, { 30.0f, 30.0f });
    entity mouse_selection;

    Camera2D camera = { 0 };
    camera.target = p.p.trlv();
    camera.offset = Vector2 { 
        (SCREEN_WIDTH / 2.0f) - p.s.x / 2,
        (SCREEN_HEIGHT / 2.0f) - p.s.x / 2
    };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    std::vector<entity> blocks;
    v2 swap;

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        if (IsKeyDown(KEY_A)) p.v.x = -ac;
        else if (IsKeyDown(KEY_D)) p.v.x = ac;
        else p.v.x = 0;

        if (IsKeyPressed(KEY_SPACE)) p.v.y = -jf;
        //if (p.v.y < 400.0f) p.v.y += g;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse_selection.p = GetMousePosition();
            mouse_selection.p.x -= camera.offset.x;
            mouse_selection.p.y -= camera.offset.y;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mouse_selection.s = GetMousePosition();
            mouse_selection.s.x -= camera.offset.x;
            mouse_selection.s.y -= camera.offset.y;

            mouse_selection.s -= mouse_selection.p;

            if (mouse_selection.s < mouse_selection.p) {
                //mouse_selection.s.x = std::max(
                //);
            }

        }

        for (entity block : blocks) {
            collisions::resolve_collision(&p, &block, dt);
        }
        camera.target = p.p.trlv();

        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode2D(camera);
                for (entity block : blocks) {
                    DrawRectangleV(block.p.trlv(), block.s.trlv(), BLACK);
                }
                DrawRectangleV(p.p.trlv(), p.s.trlv(), WHITE);

                DrawRectangleV(mouse_selection.p.trlv(), mouse_selection.s.trlv(), BLACK);
            EndMode2D();
        EndDrawing();

        p.p += p.v * dt;
    }

    CloseWindow();
}
