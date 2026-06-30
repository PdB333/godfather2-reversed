// FUNC_NAME: Sentient::isTargetVisible
// Address: 0x006ba510
// Role: Checks if the entity can see a target position (param_2) or an alternate target (param_3).
// Returns true if the target is outside a close range, and either the entity has a certain flag
// (bit 1 of +0x54) or the alternate target is beyond a medium range and has line-of-sight (via FUN_006c0050).
bool Sentient::isTargetVisible(float *targetPos, float *alternatePos) {
    // Position of this entity (offset +0xC0 = x, +0xC4 = y, +0xC8 = z)
    float dx = *(float *)(this + 0xC0) - targetPos[0];
    float dy = *(float *)(this + 0xC4) - targetPos[1];
    float dz = *(float *)(this + 0xC8) - targetPos[2];
    float distSq = dz*dz + dy*dy + dx*dx;

    // If distance to targetPos is very small (inside close range), consider not visible
    if (distSq < _DAT_00d5e6f8) {
        return false;
    }

    // Check a flag at +0x54 (bit 1). If not set, also check alternatePos
    uint flags = *(uint *)(this + 0x54);
    bool quickFlag = (flags >> 1) & 1;  // bit 1

    if (!quickFlag) {
        // Compute distance to alternatePos
        dx = *(float *)(this + 0xC0) - alternatePos[0];
        dy = *(float *)(this + 0xC4) - alternatePos[1];
        dz = *(float *)(this + 0xC8) - alternatePos[2];
        distSq = dz*dz + dy*dy + dx*dx;

        // If far away, no line-of-sight needed? Actually condition: distSq < medium threshold
        if (distSq < _DAT_00d5e6fc) {
            // Check line-of-sight from this position (at +0xC0) to origin? The call uses zero params
            // but likely a line-of-sight check: (this + 0xC0) is the starting point, 0,0 are dummy?
            // Actually FUN_006c0050(this + 0xC0, 0, 0) probably checks if point is in shadow/blocked.
            // Returns false if blocked.
            char losResult = FUN_006c0050(this + 0xC0, 0, 0);
            if (losResult == 0) {
                return false;
            }
        }
    }

    return true;
}