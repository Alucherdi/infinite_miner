#ifndef IM_MAP_L
#define IM_MAP_L

class Map {
    private:
        int x = 0, y = 0;
        int wInit, hInit;
        int bw = 10, bh = 10;
        void draw_block(int, int, int, int, bool);

    public:
        void draw();
        Map();
};

#endif
