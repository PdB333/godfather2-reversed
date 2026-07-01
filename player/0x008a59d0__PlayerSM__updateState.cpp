// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(uint thisPtr)
{
    uint flags;
    char condition;

    updateCommon();
    if (gSomeManager != nullptr) {
        if (*(int *)(thisPtr + 0x36c) != 0) {
            disableInput(0);
        }
        if (gSomeManager != nullptr) {
            (*(void (__thiscall **)(int))(*(int *)gSomeManager))(1);
        }
    }
    if ((*(byte *)(thisPtr + 0x37c) & 1) != 0) {
        condition = checkCondition();
        if ((condition != '\0') && (gSomeFlag != 0)) {
            playSound();
            return;
        }
        flags = *(uint *)(thisPtr + 0x37c);
        if ((flags >> 8 & 1) == 0) {
            if ((flags >> 4 & 1) == 0) {
                gStateID = 0x1b;
                *(uint *)(thisPtr + 0x37c) = *(uint *)(thisPtr + 0x37c) & 0xfffffff7; // clear bit 3
                setState(1);
                *(uint *)(thisPtr + 0x37c) = *(uint *)(thisPtr + 0x37c) & 0xfffffffd; // clear bit 1
            }
            else {
                if ((*(int *)(gSomePointer + 0x40) != 0) || (*(int *)(gAnotherPointer + 0xc) == 0)) {
                    handleState();
                    return;
                }
                if ((*(int *)(thisPtr + 0x3b4) == -1) && ((flags >> 0xd & 1) == 0)) {
                    *(uint *)(thisPtr + 0x37c) = *(uint *)(thisPtr + 0x37c) & 0xfffffff7;
                    setState(3);
                    *(uint *)(thisPtr + 0x37c) = *(uint *)(thisPtr + 0x37c) & 0xfffffffd;
                    return;
                }
            }
        }
    }
    return;
}