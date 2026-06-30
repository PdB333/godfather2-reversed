// FUNC_NAME: Entity::isWithinRadius
// Address: 0x006e5cd0
// Checks if the squared distance from this object's position (offsets +0x44, +0x48, +0x4c) to a given point is less than a global threshold.
// Returns 1 if within radius, 0 otherwise.

bool Entity::isWithinRadius(float* point) const {
    float dx = point[0] - *(float*)((uint8_t*)this + 0x44); // X difference
    float dz = point[2] - *(float*)((uint8_t*)this + 0x4C); // Z difference
    float dy = point[1] - *(float*)((uint8_t*)this + 0x48); // Y difference

    float distSq = dx * dx + dz * dz + dy * dy;
    // DAT_00d5faf4: global proximity threshold squared
    if (distSq < kProximityThresholdSquared) {
        return true;
    }
    return false;
}