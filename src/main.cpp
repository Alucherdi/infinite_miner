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
    entity ms;

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

    v2 mmax;
    v2 mmin;
    v2 mousepos;
    v2 offset;

    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        offset.x = camera.offset.x - camera.target.x;
        offset.y = camera.offset.y - camera.target.y;
        mousepos = GetMousePosition();
        mousepos.x -= offset.x;
        mousepos.y -= offset.y;

        if (IsKeyDown(KEY_A)) p.v.x = -ac;
        else if (IsKeyDown(KEY_D)) p.v.x = ac;
        else p.v.x = 0;

        if (IsKeyPressed(KEY_SPACE)) p.v.y = -jf;
        if (p.v.y < 400.0f) p.v.y += g;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ms.p = GetMousePosition();
            ms.p.x -= offset.x;
            ms.p.y -= offset.y;

            mmin = ms.p;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            ms.s = GetMousePosition();
            ms.s.x -= offset.x;
            ms.s.y -= offset.y;
            mmax = ms.s;
            
            if (ms.s < ms.p) {
                mmax = v2::max(ms.s, ms.p);
                mmin = v2::min(ms.s, ms.p);
            }

            ms.s -= ms.p;
            mmax -= mmin;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            blocks.push_back(entity(mmin, mmax));
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
                DrawRectangleV(p.p.trlv(), p.s.trlv(), GREEN);

                DrawRectangleV(mmin.trlv(), mmax.trlv(), BLACK);
                DrawCircleV(mousepos.trlv(), 3.0f, GREEN);
            EndMode2D();
        EndDrawing();

        p.p += p.v * dt;
    }

    CloseWindow();
}
