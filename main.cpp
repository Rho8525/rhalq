#include <raylib.h>
#include <raymath.h>
#include <vector>

static float gravity = 9.81f;
static const int width = 800;
static const int height = 450;

class Player {
  public:
    Vector2 pos;
    float size = 25.0f;
    float speed = 500.0;
    Vector2 vel = {0.0f, 0.0f};
    short dir = 0;
    short forward = 0;
    bool isShooting = false;
    bool isAlive = true;
    Player(Vector2 p = {0, 0}) {
      pos = p;
    }
    void update(float dt) {
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
    void draw(void) {
      DrawCircleV(pos, size, MAROON);
    }
};

class Bullet {
  public:
    Vector2 pos;
    Vector2 vel;
    float life = 1.0f;
    float size = 5.0f;
    Bullet(Vector2 p, Vector2 v) {
      pos = p;
      vel = v;
    }
    void update(void) {
      pos.x += vel.x;
      pos.y += vel.y;

      vel.x *= 0.8f;
      vel.y *= 0.8f;

      life -= 0.05f;
    }
    void draw(void) {
        Color c = Fade(RED, life);
        DrawCircleV(pos, size, c);
    }
    bool isDead(void) const { return life <= 0; }
};

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
      (*it)->update();
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
