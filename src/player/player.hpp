#ifndef IM_PLAYER_L
#define IM_PLAYER_L

#include <raylib.h>

class Player {
    private:
        void handle_inputs();
        void apply_gravity();
        bool inFloor = false;

    public:
        Vector2 pos;
        Vector2 size;
        Vector2 vel = Vector2 { 0.0f, 0.0f };
        Player(Vector2, Vector2);
        void update();
        void draw();
};

#endif
