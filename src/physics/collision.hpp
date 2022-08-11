#ifndef IM_COLLISION_L
#define IM_COLLISION_L

#include "rigidbody.hpp"
#include <cmath>
#include <memory>
#include <raylib.h>

#include <iostream>

class Collision {
    public:
        // Point to Rectangle
        static bool check(const Vector2 &a, const Rectangle &b) {
            return (
                a.x >= b.x &&
                a.y >= b.y &&
                a.x <  b.x + b.width && 
                a.y <  b.y + b.height
           );
        }

        // Rectangle to Rectangle
        static bool check(const Rectangle &a, const Rectangle &b) {
            return (
                a.x + a.width  > b.x &&
                a.y + a.height > b.y &&
                a.x < b.x + b.width && 
                a.y < b.y + b.height
           );
        }

        // Ray to Rectangle
        static bool check(
            const Vector2 &origin,
            const Vector2 &direction,
            const Rectangle* target,
            Vector2 &contact_point,
            Vector2 &contact_normal,
            float &near_hit
        ) {
            contact_normal = { 0.0f, 0.0f };
            contact_point = { 0.0f, 0.0f };

            Vector2 inv_dir = (Vector2) {
                1.0f / direction.x,
                1.0f / direction.y
            };

            Vector2 near_col = Vector2 {
                (target->x - origin.x) * inv_dir.x,
                (target->y - origin.y) * inv_dir.y
            };

            Vector2 far_col = Vector2 {
                (target->x + target->width  - origin.x) * inv_dir.x,
                (target->y + target->height - origin.y) * inv_dir.y
            };

            if (near_col.x > far_col.x) std::swap(near_col.x, far_col.x);
            if (near_col.y > far_col.y) std::swap(near_col.y, far_col.y);

            if (
                near_col.x > far_col.y ||
                near_col.y > far_col.x
            ) return false;

            near_hit       = std::max(near_col.x, near_col.y);
            float far_hit  = std::max(far_col.x, far_col.y);

            if (far_hit < 0) return false;

            contact_point = Vector2 {
                origin.x + near_hit * direction.x,
                origin.y + near_hit * direction.y
            };

            if (near_col.x > near_col.y) {
                if (inv_dir.x < 0) { 
                    contact_normal = (Vector2) { 1, 0 };
                } else {
                    contact_normal = (Vector2) { -1, 0 };
                }
            } else if (near_col.x < near_col.y) {
                if (inv_dir.y < 0) {
                    contact_normal = (Vector2) { 0, 1 };
                } else {
                    contact_normal = (Vector2) { 0, -1 };
                }
            }

            return true;
        }

        // Moving rectangles
        static bool check_collision(
            const RigidBody *rb_a,
            const RigidBody &rb_b,
            Vector2 &contact_point,
            Vector2 &contact_normal,
            float &contact_time,
            const float &elapsed_time
        ) {
            Rectangle a = rb_a->body;
            Vector2 vel = rb_a->vel;

            if (vel.x == 0.0f && vel.y == 0.0f)
                return false;

            Rectangle b = rb_b.body;

            Rectangle expanded_target;
            expanded_target.x = b.x - (a.width / 2);
            expanded_target.y = b.y - (a.height / 2);

            expanded_target.width = b.width + a.width;
            expanded_target.height = b.height + a.height;

            if (
                check(
                    (Vector2) {
                        a.x + (a.width / 2),
                        a.y + (a.height / 2)
                    },
                    (Vector2) {
                        vel.x * elapsed_time,
                        vel.y * elapsed_time
                    },
                    &expanded_target,
                    contact_point,
                    contact_normal,
                    contact_time
                )
            ) {
                return (contact_time >= 0.0f && contact_time < 1.0f);
            }

            return false;
        }

        static bool resolve_dynamic_ray_collision(
            RigidBody* dynamic_body,
            RigidBody* static_body,
            const float time_step,
            Vector2* cp
        ) {
            Vector2  cn;
            float contact_time = 0.0f;

            if (check_collision(
                dynamic_body, *static_body,
                *cp, cn, contact_time,
                time_step
            )) {
                dynamic_body->vel = (Vector2) {
                    cn.x * std::abs(dynamic_body->vel.x) * (1 - contact_time),
                    cn.y * std::abs(dynamic_body->vel.y) * (1 - contact_time)
                };

                std::cout << contact_time << "\n";
            }
            return true;
        }
};

#endif
