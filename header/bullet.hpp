#pragma once
#include <raylib.h>

class Bullet {
    public:
        Vector2 pos;
        Vector2 vel;
        float life;
        float size;
        Bullet(Vector2 p, Vector2 v);
        void update(float dt);
        void draw(void);
        bool isDead(void);
};