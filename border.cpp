#include "header/border.hpp"
#include "header/enemy.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Border::Border(Vector2 p, Vector2 v) {
    pos =  p;
    vel = v;
    life = 1.0f;
    size = 5.0f;
};

void Border::update(float dt) {
    pos.x += vel.x;
    pos.y += vel.y;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    life -= 0.02f;
};

void Border::check(Enemy* enemy) {
    float dist = hypot(pos.x - enemy->pos.x, pos.y - enemy->pos.y);
    if (dist - size - enemy->size <= 1.0f) {
        std::cout << "hit" << std::endl;
    }
}

void Border::draw(void) {
    Color c = Fade(RED, life);
    DrawCircleV(pos, size, c);
};

bool Border::isDead(void) {
    return life <= 0;
};