#ifndef IM_COLLISION_L
#define IM_COLLISION_L

#include <raylib.h>
#include <iostream>

#include "entity.hpp"
#include "v2.hpp"

struct collisions { 
    static bool check_ray_rectangle_col(
        v2&     origin,
        v2&     direction,
        entity* target,
        v2&     contact_point,
        v2&     contact_normal,
        float&  near_hit
    ) {
        contact_normal = v2();
        contact_point = v2();

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
            if (inv_dir.x < 0) contact_normal = v2(1.0f, 0.0f);
            else contact_normal = v2(-1.0f, 0.0f);
        } else if (near_col.x < near_col.y) {
            if (inv_dir.y < 0) contact_normal = v2(0.0f, 1.0f);
            else contact_normal = v2(0.0f, -1.0f);
        }

        return true;
    }

    static bool check_dynamic_collision(
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

    static bool resolve_collision(
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
};

#endif
