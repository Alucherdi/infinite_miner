#ifndef IM_PLAYER_L
#define IM_PLAYER_L

#include <raylib.h>

class Player {
    public:
        Vector2 pos;
        Vector2 size;
        Player(Vector2, Vector2);
        void update();
        void draw();
};

#endif
