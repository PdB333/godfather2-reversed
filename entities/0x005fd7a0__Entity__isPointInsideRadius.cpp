// FUNC_NAME: Entity::isPointInsideRadius

class Entity {
public:
    // Offsets: +0x10 = position.x, +0x14 = position.y, +0x18 = radius
    float position[2]; // +0x10
    float radius;       // +0x18

    // Checks if a given 2D point (param_2) lies within the entity's circular range.
    // Returns 1 if inside, 0 otherwise.
    int __thiscall isPointInsideRadius(float *point) {
        float dx = point[0] - position[0];
        float dy = point[1] - position[1];
        if (dx * dx + dy * dy < radius * radius) {
            return 1;
        }
        return 0;
    }
};