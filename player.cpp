#include "header/player.hpp"
#include <raylib.h>
#include <raymath.h>

Player::Player(Vector2 p) {
    pos = p;
    layer = 3;
    size = 25.0f;
    csize = 25.0f;
    speed = 500.0f;
    vel = {0.0f, 0.0f};
    dir = 0;
    forward = 0;
    isShooting = false;
    isDodging = false;
    isAlive = true;
}

void Player::update(float dt) {
    Vector2 input = { (float)dir, (float)forward };
    if (input.x != 0 || input.y != 0) {
        input = Vector2Normalize(input);
        vel.x = input.x * speed;
        vel.y = input.y * speed;
    }

    if (isDodging) {
        vel.x *= 10;
        vel.y *= 10;
        isDodging = false;
    }

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x *= 0.8f;
    vel.y *= 0.8f;

    if (isShooting) {
        csize -= 5.0f;
        isShooting = false;
    }

    if (csize < 25.0f) {
        csize += 0.05f;
    }

    if (csize <= 5.0f) {
        if (layer > 0) {
            layer--;
            csize = size;
        } else {
            isAlive = false;
        }
    }

    if (!isAlive) csize = size; isAlive = true;
}

void Player::draw(void) {
    DrawCircleV(pos, csize, MAROON);
    DrawCircleV(pos, 3, RED);
}