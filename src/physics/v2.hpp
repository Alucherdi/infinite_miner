#ifndef IM_VECTOR2_L
#define IM_VECTOR2_L

#include <raylib.h>
#include <iostream>

struct v2 {
    float x, y;
    v2() : x(0), y(0) {}
    v2(float _x, float _y) : x(_x), y(_y) {}
    v2(const v2& v) : x(v.x), y(v.y) {}

    v2 operator=(const v2 o) {
        return v2(this->x = o.x, this->y = o.y);
    }
    v2 operator=(const Vector2 o) {
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


    v2& operator+=(const v2& o) {
        this->x += o.x;
        this->y += o.y;
        return *this;
    }
    v2& operator+=(const float o) {
        this->x += o;
        this->y += o;
        return *this;
    }

    v2& operator-=(const v2& o) {
        this->x -= o.x;
        this->y -= o.y;
        return *this;
    }
    v2& operator-=(const float o) {
        this->x -= o;
        this->y -= o;
        return *this;
    }

    bool operator<(const v2& o) {
        return (this->x < o.x && this->y < o.y);
    }

    static v2 max(const v2& a, const v2& b) {
        return v2(
            std::max(a.x, b.x),
            std::max(a.y, b.y)
        );
    }
    static v2 min(const v2& a, const v2& b) {
        return v2(
            std::min(a.x, b.x),
            std::min(a.y, b.y)
        );
    }

    static v2 abs(const v2& o) {
        return v2(
            std::abs(o.x),
            std::abs(o.y)
        );
    }

    Vector2 trlv() { return Vector2 {
        this->x, this->y
    };}
};

#endif
