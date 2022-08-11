#include <raylib.h>
#include <iostream>
#include <vector>

struct v2 {
    float x, y;
    v2() : x(0), y(0) {}
    v2(float _x, float _y) : x(_x), y(_y) {}
    v2(const v2& v) : x(v.x), y(v.y) {}

    v2 operator = (const v2 o) {
        return v2(this->x = o.x, this->y = o.y);
    }

    friend v2 operator+(const v2& lp, const v2& rp) {
        return v2(lp.x + rp.x, lp.y + rp.y);
    }
    friend v2 operator+(const v2& lp, const float rp) {
        return v2(lp.x + rp, lp.y + rp);
    }
    friend v2 operator+(const float lp, const v2& rp) {
        return rp + lp;
    }

    friend v2 operator-(const v2& lp, const v2& rp) {
        return v2(lp.x - rp.x, lp.y - rp.y);
    }
    friend v2 operator-(const v2& lp, const float rp) {
        return v2(lp.x - rp, lp.y - rp);
    }
    friend v2 operator-(const float lp, const v2& rp) {
        return rp - lp;
    }

    friend v2 operator*(const v2& lp, const v2& rp) {
        return v2(lp.x * rp.x, lp.y * rp.y);
    }
    friend v2 operator*(const v2& lp, const float rp) {
        return v2(lp.x * rp, lp.y * rp);
    }
    friend v2 operator*(const float lp, const v2& rp) {
        return rp * lp;
    }

    friend v2 operator/(const v2& lp, const v2& rp) {
        return v2(lp.x / rp.x, lp.y / rp.y);
    }
    friend v2 operator/(const v2& lp, const float rp) {
        return v2(lp.x / rp, lp.y / rp);
    }
    friend v2 operator/(const float lp, const v2& rp) {
        return v2(lp / rp.x, lp / rp.y);
    }


    v2& operator += (const v2& o) {
        this->x += o.x;
        this->y += o.y;
        return *this;
    }
    v2& operator += (const float o) {
        this->x += o;
        this->y += o;
        return *this;
    }

    Vector2 trlv() { return Vector2 {
        this->x, this->y
    };}
};

struct entity {
    v2 p, s, v;
    entity() : p(), s(), v() {}
    entity(v2 _p, v2 _s, v2 _v) : p(_p), s(_s), v(_v) {}
    entity(v2 _p, v2 _s) : p(_p), s(_s), v() {}
};

bool check_ray_rectangle_col(
    v2&     origin,
    v2&     direction,
    entity* target,
    v2&     contact_point,
    v2&     contact_normal,
    float&  near_hit
) {
    contact_normal = { 0.0f, 0.0f };
    contact_point = { 0.0f, 0.0f };

    v2 inv_dir = 1.0f / direction;

    v2 near_col = (target->p - origin) * inv_dir;
    v2 far_col = (target->p + target->s - origin) * inv_dir;

    if (near_col.x > far_col.x) std::swap(near_col.x, far_col.x);
    if (near_col.y > far_col.y) std::swap(near_col.y, far_col.y);

    if (near_col.x > far_col.y ||
        near_col.y > far_col.x) {
        return false;
    }

    near_hit = std::max(near_col.x, near_col.y);
    float far_hit = std::max(far_col.x, far_col.y);

    if (far_hit < 0) {
        return false;
    }

    contact_point = (origin + near_hit) * direction;

    if (near_col.x > near_col.y) {
        if (inv_dir.x < 0) contact_normal = { 1.0f, 0.0f };
        else contact_normal = { -1.0f, 0.0f };
    } else if (near_col.x < near_col.y) {
        if (inv_dir.y < 0) contact_normal = { 0.0f, 1.0f };
        else contact_normal = { 0.0f, -1.0f };
    }

    return true;
}

bool check_dynamic_collision(
    entity* dynamic_ent,
    entity& static_ent,
    float   dt,
    v2&     contact_point,
    v2&     contact_normal,
    float&  contact_time
) {
    if (dynamic_ent->v.x == 0 && dynamic_ent->v.y == 0) {
        return false;
    }

    entity expanded_target;
    expanded_target.p = static_ent.p - dynamic_ent->s / 2;
    expanded_target.s = static_ent.s + dynamic_ent->s;

    v2 origin = dynamic_ent->p + dynamic_ent->s / 2;
    v2 direction = dynamic_ent->v * dt;

    if (check_ray_rectangle_col(
        origin,
        direction,
        &expanded_target,
        contact_point,
        contact_normal,
        contact_time
    )) {
        return (contact_time >= 0.0f && contact_time < 1.0f);
    } else {
        return false;
    }
}

bool resolve_collision(
    entity* dynamic_ent,
    entity* static_ent,
    float dt
) {
    v2 contact_point, contact_normal;
    float contact_time = 0.0f;

    if (check_dynamic_collision(
        dynamic_ent,
        *static_ent,
        dt,
        contact_point,
        contact_normal,
        contact_time
    )) {
        dynamic_ent->v += 
            contact_normal *
            v2(std::abs(dynamic_ent->v.x), std::abs(dynamic_ent->v.y)) *
            (1 - contact_time);

        return true;
    }
    return false;
}

int main() {
    InitWindow(800, 600, "");
    SetTargetFPS(144);

    float ac = 100.0f;
    float dt = 0.0f;
    float g = 40.0f;
    float jf = 800.0f;

    entity p({ 0.0f, 0.0f }, { 30.0f, 30.0f });
    entity mouse_selection;

    Camera2D camera = { 0 };
    camera.target = p.p.trlv();
    camera.offset = Vector2 { 400, 300 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    std::vector<entity> blocks;
    blocks.push_back({ { 20.0f, 50.0f }, { 20.0f, 100.0f }});
    blocks.push_back({ { 60.0f, 0.0f }, { 20.0f, 100.0f }});
    blocks.push_back({ { 200.0f, 0.0f }, { 200.0f, 100.0f }});
    blocks.push_back({ { 400.0f, 0.0f }, { 200.0f, 5.0f }});


    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        if (IsKeyDown(KEY_A)) p.v.x = -ac;
        else if (IsKeyDown(KEY_D)) p.v.x = ac;
        else p.v.x = 0;

        if (IsKeyPressed(KEY_SPACE)) p.v.y = -jf;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        }

        if (p.v.y < 400.0f) p.v.y += g;

        for (entity block : blocks) {
            resolve_collision(&p, &block, dt);
        }
        camera.target = p.p.trlv();

        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode2D(camera);
                for (entity block : blocks) {
                    DrawRectangleV(block.p.trlv(), block.s.trlv(), RED);
                }
                DrawRectangleV(p.p.trlv(), p.s.trlv(), BROWN);
            EndMode2D();
        EndDrawing();

        p.p += p.v * dt;
    }

    CloseWindow();
}
