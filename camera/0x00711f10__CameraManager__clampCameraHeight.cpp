// FUNC_NAME: CameraManager::clampCameraHeight

uint __thiscall CameraManager::clampCameraHeight(int thisPtr, float* pYCoord, uint state)
{
    float targetY;
    int iVar2;
    uint flags;

    // If state is zero, try to get it from an internal structure (+0x24c4) and adjust
    if ((state == 0) &&
        ((state = *(uint *)(*(int *)(thisPtr + 4) + 0x24c4), state != 0 &&
         (state = state - 0x48, state != 0))))
    {
        FUN_00712ff0(state, pYCoord);  // Apply some motion/damping based on state
    }

    // Subtract a global delta (likely engine step size or constant speed)
    *pYCoord -= _DAT_00d5c458;

    // Get target Y coordinate (e.g., player's height offset)
    iVar2 = FUN_00471610(); // returns pointer to some object
    targetY = *(float *)(iVar2 + 0x34);

    // Check if the Y coordinate is above targetY but within a threshold
    flags = iVar2 + 0x30; // not used? Actually param_3 is reused below
    if ((targetY <= *pYCoord) && (*pYCoord - targetY < DAT_00d5fb68))
    {
        flags = *(uint *)(*(int *)(thisPtr + 4) + 0x8e4) >> 0xe;
        if (((flags & 1) != 0) && (*(char *)(*(int *)(thisPtr + 4) + 0x1b8c) != '\0'))
        {
            // Snap Y to just above target (threshold offset)
            *pYCoord = targetY + DAT_00d5fb68;
        }
    }
    return flags;
}