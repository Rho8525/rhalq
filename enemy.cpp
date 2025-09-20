#include "header/enemy.hpp"
#include <raylib.h>
#include <raymath.h>

Enemy::Enemy(Vector2 p) {
    pos = p;
    layer = 1;
    isAlive = true;
    size = 25.0f;
    csize = 25.0f;
    speed = 100.0f;
    vel = {0.0f, 0.0f};
}

void Enemy::update(float dt, Vector2 t) {
    float angle = atan2(t.y - pos.y, t.x - pos.x);
    vel.x = cos(angle) * speed;
    vel.y = sin(angle) * speed;

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    csize -= 0.03f;

    if (csize <= 10.0f) {
        if (layer > 1) {
            --layer;
            csize = size;
        } else {
            isAlive = false;
        }
    }
}

void Enemy::draw(void) {
    DrawCircleV(pos, csize, MAROON);
}