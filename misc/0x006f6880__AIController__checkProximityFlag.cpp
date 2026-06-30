// FUNC_NAME: AIController::checkProximityFlag
uint __thiscall AIController::checkProximityFlag(int this, int shouldCheckDistance)
{
    int transformA;
    int transformB;
    uint targetHandle;
    float dx, dy, dz;
    float distSq;

    // Read a global handle from a static pointer (likely player/target manager)
    targetHandle = **(uint **)(*(int *)(gSomeGlobal + 4)); // DAT_012233a0 + 4 is a pointer to a handle

    if (targetHandle == 0) {
        return 0;
    }

    // Only perform distance check if handle is not the invalid sentinel (0x1f30) and check is requested
    if ((targetHandle != 0x1f30) && (shouldCheckDistance != 0)) {
        transformA = FUN_00471610();  // get some object's transform (first instance)
        transformB = FUN_00471610();  // get another object's transform (second instance)
        // Note: these are likely static positions from e.g., AI and target

        // Compute squared distance between two positions (offset 0x30: x, 0x34: y, 0x38: z)
        dx = *(float *)(transformB + 0x30) - *(float *)(transformA + 0x30);
        dy = *(float *)(transformB + 0x34) - *(float *)(transformA + 0x34);
        dz = *(float *)(transformB + 0x38) - *(float *)(transformA + 0x38);
        distSq = dx*dx + dy*dy + dz*dz;

        if (distSq <= *(float *)(this + 0xd4)) {
            // Within range: set low byte to 1, keep upper 24 bits of handle
            return (targetHandle & 0xffffff00) | 1;
        }
    }

    // Otherwise, clear low byte (flag) and return handle
    return targetHandle & 0xffffff00;
}