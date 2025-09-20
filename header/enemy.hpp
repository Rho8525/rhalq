#pragma once
#include <raylib.h>

class Enemy {
  public:
    Vector2 pos;
    int layer;
    bool isAlive;
    float size;
    float csize;
    float speed;
    Vector2 vel;
    Enemy(Vector2 p);
    void update(float dt, Vector2 t);
    void draw(void);
};