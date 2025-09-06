#pragma once
#include <raylib.h>

class Player {
  public:
    Vector2 pos;
    float size;
    float speed;
    Vector2 vel;
    short dir;
    short forward;
    bool isShooting;
    bool isAlive;
    Player(Vector2 p = {0, 0});
    void update(float dt);
    void draw(void);
};