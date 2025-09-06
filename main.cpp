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
  InitWindow(width, height, "RHAFQ");

  Player player = Player({0, 0});
  std::vector<Bullet*> bullets;

  Camera2D camera = { 0 };
  camera.offset = (Vector2){width/2.0f, height/2.0f};
  camera.zoom = 1.0f;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    player.update(dt);

    camera.target.x += (player.pos.x - camera.target.x) * 0.3f;
    camera.target.y += (player.pos.y - camera.target.y) * 0.3f;


    player.dir = 0;
    player.forward = 0;
    if (IsKeyDown(KEY_W)) player.forward -= 1;
    if (IsKeyDown(KEY_S)) player.forward += 1;
    if (IsKeyDown(KEY_A)) player.dir -= 1;
    if (IsKeyDown(KEY_D)) player.dir += 1;
    if (IsKeyPressed(KEY_SPACE)) {
      player.isShooting = true;
      Vector2 bulletVel = { 0, -10 };
      bullets.push_back(new Bullet(player.pos, bulletVel));
    }

    for (auto it = bullets.begin(); it != bullets.end();) {
      (*it)->update(dt);
      if ((*it)->isDead()) {
        delete *it;
        it = bullets.erase(it);
      } else {
        ++it;
      }
    }

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    BeginMode2D(camera);

    DrawCircleV((Vector2){0, 0}, 10, YELLOW);

    player.draw();

    for (auto* b : bullets) b->draw();

    EndMode2D();

    DrawText("rhalq", 10, 10, 20, MAROON);

    EndDrawing();
  }

  for (auto* b : bullets) delete b;
  CloseWindow();
  return 0;
}
