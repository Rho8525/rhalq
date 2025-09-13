#include "header/player.hpp"
#include "header/enemy.hpp"
#include "header/bullet.hpp"
#include <raylib.h>
#include <raymath.h>
#include <vector>

static float gravity = 9.81f;
static const int width = 800;
static const int height = 450;

int main(void) {
  InitWindow(width, height, "RHALQ");

  Player player = Player({0, 0});
  std::vector<Bullet*> bullets;
  std::vector<Enemy*> enemies;
  
  for (int i=0; i<20; i++) {
    enemies.push_back(new Enemy((Vector2){(float)(i * 20), 0}));
  }

  Camera2D camera = { 0 };
  camera.offset = (Vector2){width/2.0f, height/2.0f};
  camera.zoom = 1.0f;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    player.update(dt);
    player.check(enemies[0]);

    for (auto it = enemies.begin(); it != enemies.end();) {
      (*it)->update(dt, player.pos);
      ++it;
    }

    camera.target.x += (player.pos.x - camera.target.x) * 0.3f;
    camera.target.y += (player.pos.y - camera.target.y) * 0.3f;


    player.dir = 0;
    player.forward = 0;
    if (IsKeyDown(KEY_W)) player.forward -= 1;
    if (IsKeyDown(KEY_S)) player.forward += 1;
    if (IsKeyDown(KEY_A)) player.dir -= 1;
    if (IsKeyDown(KEY_D)) player.dir += 1;

    // idk if its alright
    if (IsKeyPressed(KEY_SPACE)) {
      player.isShooting = true;
      for (int i=0; i <= 360; i+=2) {
        bullets.push_back(new Bullet(player.pos, (Vector2){cos(static_cast<float>(i)) * 30, sin(static_cast<float>(i)) * 30}));
      }
    }

    for (auto it = bullets.begin(); it != bullets.end();) {
      (*it)->update(dt);
      (*it)->check(enemies[0]);
      if ((*it)->isDead()) {
        delete *it;
        it = bullets.erase(it);
      } else {
        ++it;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawCircleV((Vector2){0, 0}, 10, YELLOW);

    player.draw();

    for (auto& e : enemies) e->draw();

    for (auto& b : bullets) b->draw();

    EndMode2D();

    DrawRectangle(0, 0, 400, 100, BLUE);
    DrawText("rhalq", 10, 5, 20, MAROON);
    DrawText("wasd to move", 10, 25, 15, MAROON);
    DrawText("space to shoot", 10, 40, 15, MAROON);
    DrawText("shift to blink", 10, 55, 15, MAROON);

    EndDrawing();
  }

  for (auto& e : enemies) delete e;
  for (auto& b : bullets) delete b;
  CloseWindow();
  return 0;
}
