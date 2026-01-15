#include "01_follow_chain.hpp"

Chain::Chain(int joints_count, float joints_gap) : joints_count(joints_count), joints_gap(joints_gap) {
    joints = std::vector<Vector2>(joints_count, screen_center);
}

Chain::Chain() : joints_count(20), joints_gap(50.0f) {
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

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            DrawCircleLinesV(joints[i - 1], joints_gap, RED);
            DrawCircleLinesV(joints[i], joints_gap, RED);
        }
    }
}

void Chain::draw2() {
    float inner_radius = 12.0f;
    float outer_radius = 15.0f;

    for (int i = 1; i < joints.size(); i++) {
        DrawRing(joints[i - 1], inner_radius, outer_radius, 0, 360, 360, WHITE);

        // from joints[i - 1] to joints[i]
        Vector2 direction = {joints[i].x - joints[i - 1].x, joints[i].y - joints[i - 1].y};
        float direction_length = sqrtf(direction.x * direction.x + direction.y * direction.y);
        direction.x /= direction_length;
        direction.y /= direction_length;

        // point on joints[i - 1] circumference
        Vector2 start = {joints[i - 1].x + direction.x * outer_radius,
                         joints[i - 1].y + direction.y * outer_radius};

        // point on joints[i] circumference
        Vector2 end = {joints[i].x + direction.x * -1 * outer_radius,
                       joints[i].y + direction.y * -1 * outer_radius};

        DrawLineEx(start, end, 3.0f, WHITE);
        DrawRing(joints[i], inner_radius, outer_radius, 0, 360, 360, WHITE);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            DrawCircleLinesV(joints[i - 1], joints_gap, RED);
            DrawCircleLinesV(joints[i], joints_gap, RED);
        }
    }
}