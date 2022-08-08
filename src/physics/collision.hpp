#ifndef IM_COLLISION_L
#define IM_COLLISION_L

#include <memory>
#include <raylib.h>

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
            const Rectangle &target,
            Vector2 &contact_point,
            Vector2 &contact_normal,
            float &near_hit
        ) {
            Vector2 near_col = Vector2 {
                (target.x - origin.x) / direction.x,
                (target.y - origin.y) / direction.y
            };

            Vector2 far_col = Vector2 {
                ((target.x + target.width)  - origin.x) / direction.x,
                ((target.y + target.height) - origin.y) / direction.y
            };

            if (near_col.x > far_col.x) std::swap(near_col.x, far_col.x);
            if (near_col.y > far_col.y) std::swap(near_col.y, far_col.y);

            if (
                near_col.x > far_col.y ||
                near_col.y > far_col.x
            ) return false;

            near_hit = std::max(near_col.x, near_col.y);
            float far_hit  = std::max(far_col.x, far_col.y);

            if (far_hit < 0) return false;

            contact_point = Vector2 {
                (origin.x + near_hit) * direction.x,
                (origin.y + near_hit) * direction.y
            };

            if (near_col.x > near_col.y) {
                if (direction.x < 0) { 
                    contact_normal = (Vector2) { 1, 0 };
                } else {
                    contact_normal = (Vector2) { -1, 0 };
                }
            } else if (near_col.x < near_col.y) {
                if (direction.y < 0) {
                    contact_normal = (Vector2) { 0, 1 };
                } else {
                    contact_normal = (Vector2) { 0, -1 };
                }
            }

            return true;
        }

        // Moving rectangles
        static bool check(
            const Rectangle &a,
            const Rectangle &b,
            const Vector2 &a_vel,
            Vector2 &contact_point,
            Vector2 &contact_normal,
            float &col_time
        ) {
            if (a_vel.x == 0 && a_vel.y == 0)
                return false;

            Rectangle expanded_target;
            expanded_target.x = b.x - a.width / 2;
            expanded_target.y = b.y - a.height / 2;

            expanded_target.width = b.width + a.width;
            expanded_target.height = b.height + a.height;


            return true;
        }
};

#endif
