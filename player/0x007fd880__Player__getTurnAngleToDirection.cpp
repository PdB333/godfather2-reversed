// FUNC_NAME: Player::getTurnAngleToDirection
float __thiscall Player::getTurnAngleToDirection(int thisPtr, unsigned char direction1, unsigned char direction2)
{
    unsigned char idx1, idx2;
    float angle1, angle2, diff;

    // Map direction enum (0-4) to internal angle array index (0-3)
    // Direction mapping: 0->0, 1->2, 2->1, 3->1, 4->3, other->0xFF (invalid)
    switch (direction1) {
        case 0: idx1 = 0; break;
        case 1: idx1 = 2; break;
        case 2:
        case 3: idx1 = 1; break;
        case 4: idx1 = 3; break;
        default: idx1 = 0xFF;
    }

    // Retrieve angle for first direction from array at offset 0x1C90
    // Each entry is 8 bytes (likely a struct with angle + padding or secondary value)
    if (idx1 < 4) {
        angle1 = *(float*)(thisPtr + 0x1C90 + idx1 * 8);
    } else {
        angle1 = 0.0f;
    }

    // Same mapping for second direction
    switch (direction2) {
        case 0: idx2 = 0; break;
        case 1: idx2 = 2; break;
        case 2:
        case 3: idx2 = 1; break;
        case 4: idx2 = 3; break;
        default: idx2 = 0xFF;
    }

    if (idx2 < 4) {
        angle2 = *(float*)(thisPtr + 0x1C90 + idx2 * 8);
    } else {
        angle2 = 0.0f;
    }

    // Compute signed angular difference (angle1 - angle2)
    diff = angle1 - angle2;

    // If negative, adjust by full circle (360.0 stored at DAT_00e44564)
    // Note: This yields (360.0 - diff) which is not standard normalization,
    // but rather the complement for turning in opposite direction.
    if (diff < 0.0f) {
        return DAT_00e44564 - diff; // DAT_00e44564 is likely 360.0f
    }
    return diff;
}