// FUNC_NAME: Entity::isPointInFront
// Address: 0x006d0b00
bool __thiscall Entity::isPointInFront(Entity* this, float* point) {
    // Offsets:
    // +0x10 : positionX? (float)
    // +0x18 : positionZ? (float) — assuming 2D plane (x, z) or (x, y)
    // +0x50 : forwardX? (float)
    // +0x58 : forwardZ? (float)
    // Global _DAT_00d577a0 : dot product threshold (likely 0.0f for "in front" or configurable)

    float dx = point[2] - *(float*)((unsigned int)this + 0x18);
    float dy = point[0] - *(float*)((unsigned int)this + 0x10);
    float dot = *(float*)((unsigned int)this + 0x58) * dx +
                *(float*)((unsigned int)this + 0x50) * dy;

    // If dot product exceeds threshold, point is considered "in front"
    if (dot > _DAT_00d577a0) {
        return true;
    }
    return false;
}