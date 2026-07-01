// FUNC_NAME: Sentient::isTargetInAimCone
int __thiscall Sentient::isTargetInAimCone(int this)
{
    int targetPtr;
    int basePtr;
    float dx, dy, dz;
    float dotResult;
    float scaleFactor;
    int transformA, transformB, aimDirTransform, checkDirTransform;
    float vx, vy, vz;
    float magnitude;
    int result;

    targetPtr = *(int *)(this + 0x24CC); // +0x24CC: pointer to target entity or component
    if (targetPtr == 0) {
        basePtr = 0;
    } else {
        basePtr = targetPtr - 0x48; // offset to some sub-object (e.g., hitbox)
    }
    if (basePtr == 0) {
        // If the target sub-object is invalid, return a handle (bits 8..31 from targetPtr, low byte set to 1)
        return (targetPtr & 0xFFFFFF00) | 1;
    }

    // Retrieve two transforms to compute the vector from source to target
    transformA = FUN_00471610(); // Returns pointer to transform (e.g., shooter's weapon/head)
    transformB = FUN_00471610(); // Returns pointer to target's transform (e.g., target's chest)
    dx = *(float *)(transformB + 0x30) - *(float *)(transformA + 0x30); // X difference
    dy = *(float *)(transformB + 0x34) - *(float *)(transformA + 0x34); // Y difference
    dz = *(float *)(transformB + 0x38) - *(float *)(transformA + 0x38); // Z difference

    // Retrieve aim direction and check direction transforms
    aimDirTransform = FUN_00471610(); // Returns pointer to matrix containing aim direction vector
    checkDirTransform = FUN_00471610(); // Returns pointer to matrix containing check direction vector

    // Project the difference vector onto the aim direction, scale by a global factor
    scaleFactor = DAT_00d5ccf8; // Aim cone scaling constant
    dotResult = (*(float *)(aimDirTransform + 0x10) * dx +
                 *(float *)(aimDirTransform + 0x14) * dy +
                 *(float *)(aimDirTransform + 0x18) * dz) * scaleFactor;

    // Adjust the difference vector by pushing it along the aim direction
    dx += *(float *)(aimDirTransform + 0x10) * dotResult;
    dy += *(float *)(aimDirTransform + 0x14) * dotResult;
    dz += *(float *)(aimDirTransform + 0x18) * dotResult;

    // Dot product of the adjusted vector with the check direction
    vx = *(float *)(checkDirTransform + 0x20);
    vy = *(float *)(checkDirTransform + 0x24);
    vz = *(float *)(checkDirTransform + 0x28);
    magnitude = sqrtf(dx*dx + dy*dy + dz*dz);
    if ( ((vx*dx + vy*dy + vz*dz) / magnitude) <= _DAT_00d65ffc ) {
        // Inside the cone; return 0 (via high byte)
        result = 0;
    } else {
        // Outside the cone; return 1 (preserve high byte from earlier calculation)
        result = 1;
    }
    return result;
}