// FUNC_NAME: ChaseCamera::computeTargetOffset
void __thiscall ChaseCamera::computeTargetOffset(int this, float *outPosition)
{
    float scaleFactor = DAT_00e51cb0;
    int entityPtr;
    float offsetX, offsetY, offsetZ;

    // Get entity from transform pointer stored at +0x7c (adjusted by -0x48 to reach entity base)
    if (*(int *)(this + 0x7c) == 0) {
        entityPtr = 0;
    } else {
        entityPtr = *(int *)(this + 0x7c) - 0x48;
    }

    // Select offset vector based on mode at +0x88
    if (*(int *)(this + 0x88) == 0) {
        // Mode 0: read from entity +0x90 (two floats as double) and +0x98
        offsetX = *(float *)(entityPtr + 0x90);                         // +0x90
        offsetY = *(float *)(entityPtr + 0x94);                         // +0x94 (second float from double)
        offsetZ = *(float *)(entityPtr + 0x98);                         // +0x98
    } else if (*(int *)(this + 0x88) == 1) {
        // Mode 1: read from entity +0x70 (two floats as double) and +0x78
        offsetX = *(float *)(entityPtr + 0x70);                         // +0x70
        offsetY = *(float *)(entityPtr + 0x74);                         // +0x74
        offsetZ = *(float *)(entityPtr + 0x78);                         // +0x78
    } else {
        // Mode default: mirror by subtracting entity's vectors from global constant
        offsetX = DAT_00e44564 - *(float *)(entityPtr + 0x70);          // +0x70
        offsetY = DAT_00e44564 - *(float *)(entityPtr + 0x74);          // +0x74
        offsetZ = DAT_00e44564 - *(float *)(entityPtr + 0x78);          // +0x78
    }

    // Re-fetch entity pointer (needed for +0xb0 base position)
    if (*(int *)(this + 0x7c) == 0) {
        entityPtr = 0;
    } else {
        entityPtr = *(int *)(this + 0x7c) - 0x48;
    }

    // Apply scaling and add entity's base position (+0xb0)
    offsetZ = scaleFactor * offsetZ;
    outPosition[0] = scaleFactor * offsetX + *(float *)(entityPtr + 0xb0);  // +0xb0
    outPosition[1] = scaleFactor * offsetY + *(float *)(entityPtr + 0xb4);  // +0xb4
    outPosition[2] = offsetZ + *(float *)(entityPtr + 0xb8);                // +0xb8

    return;
}