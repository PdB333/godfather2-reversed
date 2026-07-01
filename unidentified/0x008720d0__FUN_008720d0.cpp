// FUNC_NAME: UnknownClass::updatePositionWithOffset
void __thiscall UnknownClass::updatePositionWithOffset(int thisPtr, int param0, int param1, int param2)
{
    // Check if position has been initialized
    if (*(char *)(thisPtr + 0x25) == '\0') {
        // Get some global manager or object
        int managerPtr = FUN_00471610();
        // Copy initial position from manager (offsets 0x30, 0x38 -> 8 bytes x/y, 4 bytes z)
        *(undefined8 *)(thisPtr + 0x18) = *(undefined8 *)(managerPtr + 0x30);
        *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(managerPtr + 0x38);

        // Get an offset vector (probably velocity or direction)
        float *offset = (float *)FUN_0086d500();
        // Apply scaled offset using global time delta (DAT_00d76128)
        *(float *)(thisPtr + 0x18) = *offset * DAT_00d76128 + *(float *)(thisPtr + 0x18);
        *(float *)(thisPtr + 0x1c) = offset[1] * DAT_00d76128 + *(float *)(thisPtr + 0x1c);
        *(float *)(thisPtr + 0x20) = offset[2] * DAT_00d76128 + *(float *)(thisPtr + 0x20);
        *(char *)(thisPtr + 0x25) = 1;  // Mark as initialized
    }

    // Pack position into separate parts for the call
    int z = *(int *)(thisPtr + 0x20);
    long long xy = *(long long *)(thisPtr + 0x18);
    FUN_00871900(&xy, param0, param1, param2);  // Pass position (xy as double, z as int) to some function
    return;
}