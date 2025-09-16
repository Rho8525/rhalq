#include "header/player.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "header/enemy.hpp"

// init player
Player::Player(Vector2 p) {
    pos = p;
    max_hp = 100;
    hp = max_hp;
    layer = 3;
    size = 25.0f;
    csize = 25.0f;
    xp = 0;
    speed = 500.0f;
    vel = {0.0f, 0.0f};
    dir = 0;
    forward = 0;
    isShooting = false;
    isAlive = true;
}

// update player
void Player::update(float dt) {
    // handle movement
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

    // handle shooting
    if (isShooting) {
        // reduce size when shooting
        csize -= 5.0f;
        isShooting = false;
    }

    if (csize < 25.0f) {
        // slowly get bigger
        csize += std::min(0.05f, size - csize);
    }

    // if get  too small
    if (csize <= 5.0f) {
        if (layer > 0) {
            layer--;
            csize = size;
        } else {
            isAlive = false;
        }
    }

    xp += 2;

    // if dead
    if (!isAlive) csize = size; isAlive = true;
}

// draw player
void Player::draw(void) {
    DrawCircleV(pos, csize, MAROON);
    DrawCircleV(pos, 3, RED);
    DrawText("Player", pos.x - csize, pos.y - csize * 2, 10, BLACK);
}

// chech if it collide with enemy
void Player::check(Enemy* enemy) {
    float dist = hypot(pos.x - enemy->pos.x, pos.y - enemy->pos.y);
    if (dist - size - enemy->size <= 1.0f) {
        std::cout << "hit" << std::endl;
    }
}