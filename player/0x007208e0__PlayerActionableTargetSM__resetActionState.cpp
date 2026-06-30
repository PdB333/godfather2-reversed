// FUNC_NAME: PlayerActionableTargetSM::resetActionState

void __fastcall PlayerActionableTargetSM::resetActionState(int thisPtr)
{
    int iVar1; // derived pointer to enclosing object

    // Check if mActionTarget (at +0x4) is non-zero and not a special sentinel value 0x48
    if ((*(int *)(thisPtr + 4) != 0) && (*(int *)(thisPtr + 4) != 0x48)) {
        // Compute base of containing object (offset -0x48 from target pointer)
        if (*(int *)(thisPtr + 4) == 0) {
            iVar1 = 0;
        }
        else {
            iVar1 = *(int *)(thisPtr + 4) + -0x48;
        }

        // Check if movement state component (at +0x1f3c) is active
        if (*(int *)(iVar1 + 0x1f3c) != 0) {
            FUN_0072ff10(); // likely stopMovement()
        }

        // Recalculate base pointer
        if (*(int *)(thisPtr + 4) == 0) {
            iVar1 = 0;
        }
        else {
            iVar1 = *(int *)(thisPtr + 4) + -0x48;
        }

        // Check if action state flags (bits 1-3 of +0x1f98) are set
        if ((*(byte *)(iVar1 + 0x1f98) & 0xe) != 0) {
            FUN_00720750(0); // likely stopCurrentAction(false)
            *(uint *)(thisPtr + 0x20) &= 0xffffffdf; // clear bit 5 of flags
            *(int *)(thisPtr + 0x10) = 0;            // reset action counter
        }

        // Clear additional flags (bits 8-10)
        if (*(int *)(thisPtr + 4) != 0) {
            FUN_00800e60(); // likely update some internal state
            *(uint *)(thisPtr + 0x20) &= 0xfffffbf7;
            return;
        }

        // If target is zero (shouldn't happen here, but safety)
        FUN_00800e60();
    }

    // Default: clear flags regardless
    *(uint *)(thisPtr + 0x20) &= 0xfffffbf7;
    return;
}