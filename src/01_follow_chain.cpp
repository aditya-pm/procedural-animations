#include "01_follow_chain.hpp"

Chain::Chain(int joints_count, float joints_gap) : joints_count(joints_count), joints_gap(joints_gap) {
    joints = std::vector<Vector2>(joints_count, screen_center);
}

Chain::Chain() : joints_count(20), joints_gap(30.0f) {
    joints = std::vector<Vector2>(joints_count, screen_center);
}

void Chain::update() {
    Vector2 target_position = GetMousePosition();
    joints[0] = target_position;

    for (int i = 1; i < joints.size(); i++) {
        Vector2 previous_joint = joints[i - 1];
        Vector2 current_joint = joints[i];

        // direction vector from a joint to the joint after it
        Vector2 direction = {
            current_joint.x - previous_joint.x,
            current_joint.y - previous_joint.y};

        float direction_length = sqrtf(direction.x * direction.x + direction.y * direction.y);

        // normalize direction
        // if curr = prev, dir_len = 0, and / 0 = U.B, hence the check
        if (direction_length > 0.0f) {
            direction.x /= direction_length;
            direction.y /= direction_length;
        }

        // distance constraint
        joints[i] = {
            previous_joint.x + direction.x * joints_gap,
            previous_joint.y + direction.y * joints_gap};
    }
}

void Chain::draw() {
    for (int i = 1; i < joints.size(); i++) {
        DrawCircleV(joints[i - 1], 8, WHITE);
        DrawLineEx(joints[i - 1], joints[i], 5.0f, WHITE);
        DrawCircleV(joints[i], 8, WHITE);
    }
}
