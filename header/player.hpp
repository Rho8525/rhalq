#pragma once
#include <raylib.h>
#include "enemy.hpp"

class Player {
  public:
    Vector2 pos; // position
    int max_hp; // max health
    int hp; // health
    int layer; // layer or life
    float size; // max size
    float csize; // size
    unsigned int xp;
    float speed; // speed
    Vector2 vel; // velocity
    short dir; // x direction
    short forward; // y direction
    bool isShooting; // is shooting
    bool isAlive; // is alive
    Player(Vector2 p = {0, 0}); // init player or construtor
    void update(float dt); // update player
    void draw(void); // draw player
    void check(Enemy* enemy); // check if player get hit by enemy
};