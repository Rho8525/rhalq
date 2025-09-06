#include "header/enemy.hpp"
#include <raylib.h>
#include <raymath.h>

Enemy::Enemy(Vector2 p) {
    pos = p;
    size = 25.0f;
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
}

void Enemy::draw(void) {
    DrawCircleV(pos, size, MAROON);
}