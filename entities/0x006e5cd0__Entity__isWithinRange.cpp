// FUNC_NAME: Entity::isWithinRange
// Function address: 0x006e5cd0
// Checks if a given position is within a certain squared distance from this entity's position.
// Offsets: +0x44 = position.x, +0x48 = position.y, +0x4c = position.z
extern const float kSquaredRangeThreshold; // DAT_00d5faf4

bool __thiscall Entity::isWithinRange(float* targetPos) {
    float dx = targetPos[0] - *(float*)(this + 0x44); // diff in x
    float dy = targetPos[1] - *(float*)(this + 0x48); // diff in y
    float dz = targetPos[2] - *(float*)(this + 0x4c); // diff in z

    // Check squared distance against threshold
    if (dx * dx + dy * dy + dz * dz < kSquaredRangeThreshold) {
        return true;
    }
    return false;
}