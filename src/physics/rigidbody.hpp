#ifndef IM_RIGIDBODY_L
#define IM_RIGIDBODY_L

#include <array>
#include <raylib.h>

class RigidBody {
    public:
        Rectangle body;
        Vector2 vel;
        std::array<Rectangle, 4> contact;
};

#endif
