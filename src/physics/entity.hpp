#ifndef IM_ENTITY_L
#define IM_ENTITY_L

#include "v2.hpp"

struct entity {
    v2 p, s, v;
    entity() : p(), s(), v() {}
    entity(v2 _p, v2 _s, v2 _v) : p(_p), s(_s), v(_v) {}
    entity(v2 _p, v2 _s) : p(_p), s(_s), v() {}
};

#endif
