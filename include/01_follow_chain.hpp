#include <cmath>
#include <vector>

#include "config.hpp"
#include "raylib.h"

class Chain {
   private:
    const Vector2 screen_center = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    const int joints_count;
    const float joints_gap;

    std::vector<Vector2> joints;

   public:
    Chain(int joints_count, float joints_gap);
    Chain();

    void update();
    void draw();
    void draw2();
};