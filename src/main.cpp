#include <raylib.h>
#include <iostream>

struct v2 {
    float x, y;

    // another vector
    inline v2 operator = (const v2 o) {
        return (v2) { this->x = o.x, this->y = o.y };
    }

    inline v2 operator + (const v2 o) {
        return (v2) { this->x + o.x, this->y + o.y };
    }

    inline v2 operator += (const v2 o) {
        return (v2) { this->x += o.x, this->y += o.y };
    }

    inline v2 operator - (const v2 o) {
        return (v2) { this->x - o.x, this->y - o.y };
    }

    inline v2 operator * (const v2 o) {
        return (v2) { this->x * o.x, this->y * o.y };
    }

    inline v2 operator / (const v2 o) {
        return (v2) { this->x / o.x, this->y / o.y };
    }

    // float value
    inline v2 operator + (const float o) {
        return (v2) { this->x + o, this->y + o };
    }

    inline v2 operator += (const float o) {
        return (v2) { this->x += o, this->y += o };
    }

    inline v2 operator - (const float o) {
        return (v2) { this->x - o, this->y - o };
    }

    inline v2 operator * (const float o) {
        return (v2) { this->x * o, this->y * o };
    }

    inline v2 operator / (const float o) {
        return (v2) { this->x / o, this->y / o };
    }

    Vector2 trlv() { return (Vector2) {
        this->x, this->y
    };}
};

struct entity {
    v2 p, s, v;
};

int main() {
    InitWindow(300, 300, "");
    SetTargetFPS(60);

    float ac = 50.0f;
    float dt = 0.0f;

    entity p { { 0.0f, 0.0f }, { 5.0f, 5.0f }, { 0.0f, 0.0f }};

    entity b { { 30.0f, 100.0f }, { 10.0f, 10.0f }, { 0.0f, 0.0f }};

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        if (IsKeyDown(KEY_A)) p.v.x = -ac;
        else if (IsKeyDown(KEY_D)) p.v.x = ac;
        else p.v.x = 0;

        if (IsKeyDown(KEY_W)) p.v.y = -ac;
        else if (IsKeyDown(KEY_S)) p.v.y = ac;
        else p.v.y = 0;

        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangleV(p.p.trlv(), p.s.trlv(), RED);
            DrawRectangleV(b.p.trlv(), b.s.trlv(), RED);
        EndDrawing();

        p.p += p.v * dt;
    }

    CloseWindow();
}
