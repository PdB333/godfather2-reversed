// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int thisPtr) {
    char cVar1;
    uint uVar2;
    int *piVar3;
    float10 fVar4;

    // Set flag bit 3 (0x8) in state flags
    *(uint *)(thisPtr + 0x90) = *(uint *)(thisPtr + 0x90) | 8;

    // Check if flag bit 4 (0x10) is clear
    if ((*(uint *)(thisPtr + 0x90) >> 4 & 1) == 0) {
        // Set flag bit 5 (0x20) and return early
        *(uint *)(thisPtr + 0x90) = *(uint *)(thisPtr + 0x90) | 0x20;
        return;
    }

    // If component pointer is non-null and not 0x48 (likely a sentinel)
    if ((*(int *)(thisPtr + 0x88) != 0) && (*(int *)(thisPtr + 0x88) != 0x48)) {
        // Compute base class pointer by subtracting 0x48 from the component pointer
        if (*(int *)(thisPtr + 0x88) == 0) {
            piVar3 = (int *)0x0;
        } else {
            piVar3 = (int *)(*(int *)(thisPtr + 0x88) + -0x48);
        }

        // Call virtual function at vtable offset 0x1A8 (likely returns a float, e.g., current speed)
        fVar4 = (float10)(**(code **)(*piVar3 + 0x1a8))();

        // If result > global threshold (e.g., kSpeedThreshold)
        if ((float10)_DAT_00d6835c < fVar4) {
            cVar1 = FUN_00778fd0(); // Possibly a random/condition check
            if ((cVar1 != '\0') &&
                // Access a global circular buffer using bitwise index
               (uVar2 = DAT_010c2678 & DAT_012054b4, DAT_012054b4 = DAT_012054b4 + 1,
                *(float *)(&DAT_010c2680 + uVar2 * 4) <= DAT_00d68364 &&
                DAT_00d68364 != *(float *)(&DAT_010c2680 + uVar2 * 4))) {
                // Set flag bit 6 (0x40) to trigger a state transition
                *(uint *)(thisPtr + 0x90) = *(uint *)(thisPtr + 0x90) | 0x40;
                return;
            }
        }
    }

    // Recompute base class pointer (could be null)
    if (*(int *)(thisPtr + 0x88) == 0) {
        piVar3 = (int *)0x0;
    } else {
        piVar3 = (int *)(*(int *)(thisPtr + 0x88) + -0x48);
    }

    // Call virtual function at vtable offset 0x298 (likely an update/apply method)
    (**(code **)(*piVar3 + 0x298))();
    return;
}