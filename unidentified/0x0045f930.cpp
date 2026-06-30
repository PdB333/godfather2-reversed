// FUN_0045f930: Entity::getPositionState
void __thiscall Entity::getPositionState(Vector3* outPos, uint* flags) {
    // +0x218: flag indicating whether interpolation is enabled (0 = no interpolation)
    if (*(int*)(this + 0x218) == 0) {
        // Direct copy from stored position at offset 0x100 (+0x100 x, +0x104 y, +0x108 z)
        *outPos = *(Vector3*)(this + 0x100);
        return;
    }

    uint flag = *flags;
    if ((flag & 2) != 0) {
        // Bit 2 set: return zero vector
        outPos->x = 0.0f;
        outPos->y = 0.0f;
        outPos->z = 0.0f;
        return;
    }

    if ((flag & 1) != 0) {
        // Bit 1 set: call interpolation function with the remaining bits as parameter
        // FUN_00577d70 likely computes interpolated position and writes to local stack
        float local_x, local_y, local_z;
        FUN_00577d70(flag >> 2);
        outPos->x = local_x;
        outPos->y = local_y;
        outPos->z = local_z;
        return;
    }

    // No flags set: fallback to unkown function (possibly error handler)
    FUN_00577bd0();
}