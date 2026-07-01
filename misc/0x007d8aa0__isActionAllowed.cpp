// FUNC_NAME: isActionAllowed
bool __fastcall isActionAllowed(int thisPtr)
{
    // thisPtr + 0x58: pointer to some state object (e.g., player state machine)
    int* stateObj = *(int**)(thisPtr + 0x58);
    // thisPtr + 0x74: pointer to another object (e.g., input or controller)
    int* otherObj = *(int**)(thisPtr + 0x74);

    // Check bit 10 of dword at stateObj+0x8e0 is clear
    if ((*(uint*)(stateObj + 0x8e0) >> 10 & 1) != 0)
        return false;

    // Check bit 3 of byte at otherObj+4 is set
    if ((*(byte*)(otherObj + 4) & 8) == 0)
        return false;

    // Check bit 7 of dword at stateObj+0x8e4 is clear
    if ((*(uint*)(stateObj + 0x8e4) >> 7 & 1) != 0)
        return false;

    // Call global function returning a pointer to some manager/state
    int* globalObj = (int*)FUN_007ab160();
    // Check bit 2 of byte at globalObj+4 is set
    if ((*(byte*)(globalObj + 4) & 4) == 0)
        return false;

    // Check global pointer DAT_0112a838: if non-null, ensure its +0x5c is zero
    if (DAT_0112a838 != 0 && *(int*)(DAT_0112a838 + 0x5c) != 0)
        return false;

    return true;
}