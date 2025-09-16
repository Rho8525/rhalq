#include "header/border.hpp"
#include "header/enemy.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>

// initialize border, i think it should be border node but whatever
Border::Border(Vector2 p, Vector2 v, Vector2 c) {
    pos =  p;
    vel = v;
    life = 1.0f;
    size = 5.0f;
    center = c;
};

// update border
void Border::update(float dt) {
    pos.x += vel.x;
    pos.y += vel.y;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    life -= 0.02f;
};

// check if enemy hit border
void Border::check(Enemy* enemy) {
    float dist = hypot(pos.x - enemy->pos.x, pos.y - enemy->pos.y);
    if (dist - size - enemy->size <= 1.0f) {
        std::cout << "hit" << std::endl;
        float angle = atan2(enemy->pos.y - center.y, enemy->pos.x - center.x);
        float lx = cos(angle) * (hypot(pos.x - center.x, pos.y - center.y) + size + enemy->size);
        float ly = sin(angle) * (hypot(pos.x - center.x, pos.y - center.y) + size + enemy->size);
        enemy->pos = (Vector2){center.x + lx, center.y + ly};
    }
}

// draw border
void Border::draw(void) {
    Color c = Fade(RED, life);
    DrawCircleV(pos, size, c);
};

// is it time for border to  vanish
bool Border::isDead(void) {
    return life <= 0;
};