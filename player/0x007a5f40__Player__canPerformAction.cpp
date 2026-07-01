// FUNC_NAME: Player::canPerformAction
int __fastcall Player::canPerformAction(int thisPtr)
{
    uint flags;
    char isButtonHeld;
    int result;

    // Check if player is in a disabled state (0 = none, 0x48 = specific disabled state)
    if ((*(int *)(thisPtr + 0x74c) == 0) || (*(int *)(thisPtr + 0x74c) == 0x48)) {
        // Check various action flags at +0x8e0 and +0x8e4
        if ((((*(uint *)(thisPtr + 0x8e0) >> 10 & 1) == 0) &&
            ((flags = *(uint *)(thisPtr + 0x8e4), (flags >> 7 & 1) == 0) &&
             ((flags >> 6 & 1) == 0) && ((flags >> 5 & 1) == 0))) &&
            // Check if button 0x1f is not held
            (isButtonHeld = FUN_00690210(0x1f), isButtonHeld == '\0')) {
            // Check secondary action state at +0x30c0
            if ((*(int *)(thisPtr + 0x30c0) != 0) && (*(int *)(thisPtr + 0x30c0) != 0x48) &&
                ((*(uint *)(thisPtr + 0x24a0) >> 0xc & 1) == 0)) {
                return 2; // Can perform action
            }
        }
    } else {
        // Player is in a disabled state, check if can override
        result = FUN_00800ad0();
        if (result != 0) {
            return 2;
        }
        result = FUN_00800b10();
        if (result != 0) {
            return 2;
        }
    }
    return 1; // Cannot perform action
}