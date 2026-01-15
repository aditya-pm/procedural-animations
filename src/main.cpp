#include "01_follow_chain.hpp"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural Animations");
    SetTargetFPS(60);

    Chain chain;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        chain.update();
        chain.draw();

        EndDrawing();
    }

    CloseWindow();
}