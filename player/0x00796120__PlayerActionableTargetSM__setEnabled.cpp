// FUNC_NAME: PlayerActionableTargetSM::setEnabled
void __thiscall PlayerActionableTargetSM::setEnabled(int thisPtr, char enable, char forceReset)
{
    int *component;
    int enableValue;

    // If forceReset is true, clear the action state at +0x2a4 and set the dirty flag (bit 26) at +0x2bc
    if (forceReset != '\0') {
        *(int *)(thisPtr + 0x2a4) = 0;
        *(unsigned int *)(thisPtr + 0x2bc) |= 0x4000000;
    }

    // Set or clear the enabled flag (bit 0) at +0x2bc
    if (enable == '\0') {
        *(unsigned int *)(thisPtr + 0x2bc) &= 0xfffffffe;
        // Only proceed if the state at +0x2b8 is not 2 (e.g., not in a special state)
        if ((*(int *)(thisPtr + 0x2b8) != 2) ||
            (component = *(int **)(thisPtr + 0x130), component == (int *)0x0)) {
            goto LAB_00796183;
        }
        enableValue = 0;
    } else {
        *(unsigned int *)(thisPtr + 0x2bc) |= 1;
        component = *(int **)(thisPtr + 0x130);
        if (component == (int *)0x0) {
            goto LAB_00796183;
        }
        enableValue = 1;
    }

    // Call virtual function at vtable+0x44 on the component with a message ID and enable value
    (**(code **)(*component + 0x44))(0x6f74af5b, enableValue);

LAB_00796183:
    // Play a sound effect or UI feedback (FUN_00795a90 returns a handle, FUN_00794600 plays it)
    int soundHandle = FUN_00795a90(0, 1);
    FUN_00794600(soundHandle);
    return;
}