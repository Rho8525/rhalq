#include "header/bullet.hpp"
#include "header/enemy.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>

Bullet::Bullet(Vector2 p, Vector2 v) {
    pos =  p;
    vel = v;
    life = 1.0f;
    size = 5.0f;
};

void Bullet::update(float dt) {
    pos.x += vel.x;
    pos.y += vel.y;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    life -= 0.05f;
};

void Bullet::check(Enemy* enemy) {
    float dist = hypot(pos.x - enemy->pos.x, pos.y - enemy->pos.y);
    if (dist - size - enemy->size <= 1.0f) {
        std::cout << "hit" << std::endl;
    }
}

void Bullet::draw(void) {
    Color c = Fade(RED, life);
    DrawCircleV(pos, size, c);
};

bool Bullet::isDead(void) {
    return life <= 0;
};