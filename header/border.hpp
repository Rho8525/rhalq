#pragma once
#include <raylib.h>
#include "enemy.hpp"

class Border {
    public:
        Vector2 pos;
        Vector2 vel;
        float life;
        float size;
        Vector2 center;
        Border(Vector2 p, Vector2 v, Vector2 c);
        void update(float dt);
        void check(Enemy* enemy);
        void draw(void);
        bool isDead(void);
};