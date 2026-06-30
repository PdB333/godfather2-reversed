// FUNC_NAME: PlayerSM::getStateHash
uint32_t __thiscall PlayerSM::getStateHash(PlayerSM* this) {
    uint32_t stateHash = 0xC7293F9A;
    int mode = getCurrentMode(); // FUN_00800b60 - returns 1,2,3,4
    int stateMachinePtr = *(int*)(*(int*)((char*)this + 0x5C) + 0x21DC); // deref from this+0x5C -> +0x21DC
    uint8_t flags = *(uint8_t*)(stateMachinePtr + 0x88); // byte at +0x88, likely state flags

    if ((flags & 1) != 0) {
        // Bit 0 set: special state
        if (mode == 1) return 0x6039976F;
        if (mode == 2) return 0xA5E5EC2E;
        if (mode == 3) return 0xBC50CDB5;
        return 0xC7293F9A; // default
    }

    bool checkStateResult;
    if (flags == 2) {
        checkStateResult = true;
    } else if (flags == 4) {
        checkStateResult = false;
    } else {
        int checkResult = checkState(stateMachinePtr, *(int*)((char*)this + 0x5C)); // FUN_0071a640
        checkStateResult = (checkResult != 2);
    }

    if (!checkStateResult) {
        // State is 4 or checkResult == 2
        if (mode == 1) return 0xEFB6035C;
        if (mode == 2) return 0x47337595;
        if (mode == 3 || mode == 4) return 0xEC38AC6D;
    } else {
        // Other states
        if (mode == 1) return 0x76E1517F;
        if (mode == 2) return 0x70F96D86;
        if (mode == 3 || mode == 4) stateHash = 0x4419ECAE;
    }

    return stateHash;
}