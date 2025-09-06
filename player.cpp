#include "header/player.hpp"
#include <raylib.h>
#include <raymath.h>

Player::Player(Vector2 p) {
    pos = p;
    size = 25.0f;
    speed = 500.0f;
    vel = {0.0f, 0.0f};
    dir = 0;
    forward = 0;
    isShooting = false;
    isAlive = true;
}

void Player::update(float dt) {
    Vector2 input = { (float)dir, (float)forward };
    if (input.x != 0 || input.y != 0) {
        input = Vector2Normalize(input);
        vel.x = input.x * speed;
        vel.y = input.y * speed;
    }
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    if (isShooting) {
        size -= 5.0f;
        isShooting = false;
    }

    if (size < 25.0f) {
        size += 0.05f;
    }

    if (size <= 0) isAlive = false;

    if (!isAlive) size = 25.0f; isAlive = true;
}

void Player::draw(void) {
    DrawCircleV(pos, size, MAROON);
}