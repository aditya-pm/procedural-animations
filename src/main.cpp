#include <cmath>
#include <vector>

#include "raylib.h"

#define WIDTH 1200
#define HEIGHT 800

static const int JOINTS_COUNT = 20;
static const float JOINTS_GAP = 30.0f;

int main() {
    InitWindow(WIDTH, HEIGHT, "Procedural Animations");
    SetTargetFPS(60);

    // initialize all joints to be at center of screen
    std::vector<Vector2> joints(JOINTS_COUNT, {WIDTH / 2.0f, HEIGHT / 2.0f});

    while (!WindowShouldClose()) {
        Vector2 target = GetMousePosition();
        joints[0] = target;

        for (int i = 1; i < joints.size(); i++) {
            Vector2 prev_joint = joints[i - 1];
            Vector2 curr_joint = joints[i];

            // from prev to curr
            Vector2 direction = {
                curr_joint.x - prev_joint.x,
                curr_joint.y - prev_joint.y};

            float direction_length = sqrtf(direction.x * direction.x + direction.y * direction.y);

            // if curr = prev, dir_len = 0, and / 0 = U.B
            if (direction_length > 0.0001f) {
                direction.x /= direction_length;
                direction.y /= direction_length;
            }

            joints[i] = {
                prev_joint.x + direction.x * JOINTS_GAP,
                prev_joint.y + direction.y * JOINTS_GAP};
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 1; i < joints.size(); i++) {
            DrawCircleV(joints[i - 1], 8, WHITE);
            DrawLineEx(joints[i - 1], joints[i], 5.0f, WHITE);
            DrawCircleV(joints[i], 8, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}