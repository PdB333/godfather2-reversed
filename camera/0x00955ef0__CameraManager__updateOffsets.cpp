// FUNC_NAME: CameraManager::updateOffsets
void __fastcall CameraManager::updateOffsets(int thisPtr)
{
    // Check if the global state pointer (DAT_012233a0) points to a null or special value (0x1f30)
    int* globalPtr = *(int**)(DAT_012233a0 + 4);
    if (globalPtr == 0 || globalPtr == (int*)0x1f30) {
        // Clear look-at offsets if in invalid state (e.g., loading screen)
        *(int*)(thisPtr + 0xdc) = 0; // +0xDC: maybe far target Z
        *(int*)(thisPtr + 0xd8) = 0; // +0xD8: far target Y
        *(int*)(thisPtr + 0xd0) = 0; // +0xD0: far target X
    } else {
        // Get a pointer from FUN_00471610 (possibly current camera or player)
        int cameraData = FUN_00471610();
        *(int*)(thisPtr + 0xd0) = *(int*)(cameraData + 0x30); // +0x30: offset X
        *(int*)(thisPtr + 0xd4) = *(int*)(cameraData + 0x34); // +0x34: offset Y (overwritten later)
        *(int*)(thisPtr + 0xd8) = *(int*)(cameraData + 0x38); // +0x38: offset Z
        *(int*)(thisPtr + 0xdc) = *(int*)(DAT_00d5780c);     // Global look-at distance or target
    }
    // Always clear offset Y after assignment (possibly intended for certain camera modes)
    *(int*)(thisPtr + 0xd4) = 0;

    // Compute an adjusted value, likely for FOV or zoom: (baseFOV / something) * something
    float baseFov = *(float*)(thisPtr + 0xcc);   // +0xCC: base field of view or distance
    float divisor = *(float*)(thisPtr + 0xa8);    // +0xA8: divisor (screen aspect or zoom factor)
    float factor = *(float*)(thisPtr + 0xb4);     // +0xB4: multiplier
    if (divisor != 0.0f) {
        *(float*)(thisPtr + 0xc8) = (baseFov / divisor) * factor; // +0xC8: computed FOV/zoom
    } else {
        // Avoid division by zero
        *(float*)(thisPtr + 0xc8) = 0.0f;
    }

    // Clear another offset, possibly a flag or timer
    *(int*)(thisPtr + 0xfc) = 0; // +0xFC: some reset flag
}