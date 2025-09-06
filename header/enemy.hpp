#pragma once
#include <raylib.h>

class Enemy {
  public:
    Vector2 pos;
    float size;
    float speed;
    Vector2 vel;
    bool isShooting;
    bool isAlive;
    Enemy(Vector2 p = {0, 0});
    void update(float dt);
    void draw(void);
};