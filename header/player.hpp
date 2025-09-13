#pragma once
#include <raylib.h>
#include "enemy.hpp"

class Player {
  public:
    Vector2 pos;
    int layer;
    float size;
    float csize;
    float speed;
    Vector2 vel;
    short dir;
    short forward;
    bool isShooting;
    bool isAlive;
    Player(Vector2 p = {0, 0});
    void update(float dt);
    void draw(void);
    void check(Enemy* enemy);
};