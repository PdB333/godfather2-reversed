// FUNC_NAME: Entity::playSoundEffect
void __thiscall Entity::playSoundEffect(int thisPtr) {
    uint flags;
    uint count;
    float volumeOrPitch;
    int someGlobalPtr;
    int checkValue;

    // Check bit 1 of flags at +0x3d4
    if ((*(uint *)(thisPtr + 0x3d4) >> 1 & 1) != 0) {
        // If enabled, play sound with hash 0x852d191 multiple times
        count = 0;
        if (*(int *)(thisPtr + 0x3d8) != 0) {
            do {
                playSoundByHash(0x852d191);  // FUN_00894c90
                count++;
            } while (count < *(uint *)(thisPtr + 0x3d8));
        }

        // Convert integer at +0x3e0 to float (handles negative sign)
        volumeOrPitch = (float)*(int *)(thisPtr + 0x3e0);
        if (*(int *)(thisPtr + 0x3e0) < 0) {
            volumeOrPitch += DAT_00e44578;  // likely 0.0 adjustment
        }

        // Play another sound with hash 0x23ae862d using the float
        playStreamByHashAndVolume(0x23ae862d, volumeOrPitch, 0);  // FUN_00894e50

        // Access global object pointer (DAT_012233a0 + 4)
        someGlobalPtr = **(int **)(DAT_012233a0 + 4);
        if ((someGlobalPtr != 0) && (someGlobalPtr != 0x1f30)) {
            // Check some ID from the global object
            checkValue = FUN_008c74d0(*(undefined4 *)(someGlobalPtr + -0x5c));
            if (checkValue != 0) {
                // Set parameter (likely volume or state) with the integer value and 4
                FUN_008c29a0(*(int *)(thisPtr + 0x3e0), 4);
            }
        }
    }
}