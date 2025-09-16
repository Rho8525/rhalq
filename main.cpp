#include "header/player.hpp"
#include "header/enemy.hpp"
#include "header/border.hpp"
#include <raylib.h>
#include <raymath.h>
#include <vector>

// global variable
static float gravity = 9.81f;
static const int width = 800;
static const int height = 450;

// main function
int main(void) {
  InitWindow(width, height, "RHALQ");

  // define player
  Player player = Player({0, 0});
  std::vector<Border*> borders;
  std::vector<Enemy*> enemies;
  
  // spawn enemies
  for (int i=0; i<20; i++) {
    enemies.push_back(new Enemy((Vector2){(float)(i * 20), 0}));
  }

  // init 2d camera
  Camera2D camera = { 0 };
  camera.offset = (Vector2){width/2.0f, height/2.0f};
  camera.zoom = 1.0f;

  // main game loop
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    // update player
    player.update(dt);
    player.check(enemies[0]);

    // update enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
      (*it)->update(dt, player.pos);
      ++it;
    }

    // update camera
    camera.target.x += (player.pos.x - camera.target.x) * 0.3f;
    camera.target.y += (player.pos.y - camera.target.y) * 0.3f;

    // player control
    player.dir = 0;
    player.forward = 0;
    if (IsKeyDown(KEY_W)) player.forward -= 1; // go up
    if (IsKeyDown(KEY_S)) player.forward += 1; // go down
    if (IsKeyDown(KEY_A)) player.dir -= 1; // go left
    if (IsKeyDown(KEY_D)) player.dir += 1; // go right

    if (IsKeyPressed(KEY_SPACE)) {
      player.isShooting = true;
      // deploy border
      for (int i=0; i <= 360; i+=2) {
        borders.push_back(new Border(player.pos, (Vector2){cos(static_cast<float>(i)) * 30, sin(static_cast<float>(i)) * 30}, player.pos));
      }
    }

    // iterate every border
    for (auto it = borders.begin(); it != borders.end();) {
      // update border
      (*it)->update(dt);
      // check if border collide with enemy
      //(*it)->check(enemies[0]);
      for (auto e : enemies) {
        (*it)->check(e);
      }
      // check if its the time to disappear
      if ((*it)->isDead()) {
        // delete border
        delete *it;
        it = borders.erase(it);
      } else {
        // continue to the next border
        ++it;
      }
    }

    // begin drawing session
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // start camera mode
    BeginMode2D(camera);

    // draw yellow circle? :u
    DrawCircleV((Vector2){0, 0}, 10, YELLOW);

    // draw player
    player.draw();

    // draw enemies
    for (auto& e : enemies) e->draw();

    // draw border
    for (auto& b : borders) b->draw();

    // end camera mode
    EndMode2D();
    // end drawing session
    EndDrawing();
  }

  // clean entity
  for (auto& e : enemies) delete e;
  for (auto& b : borders) delete b;
  CloseWindow();
  return 0;
}
