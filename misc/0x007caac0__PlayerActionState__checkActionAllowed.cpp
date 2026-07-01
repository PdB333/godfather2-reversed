// FUNC_NAME: PlayerActionState::checkActionAllowed
uint8_t __thiscall PlayerActionState::checkActionAllowed(int thisPtr, int param2)
{
    uint8_t result = 0;
    // pStateController is at this+0x4, points to a flags field at +0x24
    int* pStateController = *(int**)(thisPtr + 4);
    uint8_t flags = *(uint8_t*)(pStateController + 0x24) & 3;

    if (flags == 0) {
        // actionType at this+0x8
        int actionType = *(int*)(thisPtr + 8);
        // counter at this+0x10
        int counter = *(int*)(thisPtr + 0x10);
        // cooldown at this+0x1c
        int cooldown = *(int*)(thisPtr + 0x1c);

        if (((actionType == 4) || (actionType == 0)) ||
            (cooldown > 5) ||
            ((counter != 0 && (*(char*)(thisPtr + 0xc) == '\0')))) {
            if ((uint32_t)counter < 4) {
                return 1;
            }
        }
    } else {
        if ((flags == 1) || (flags == 2)) {
            return 0;
        }
        if (flags == 3) {
            // Delegate to a helper function with param2
            result = FUN_007ca8b0(param2);
        }
    }
    return result;
}