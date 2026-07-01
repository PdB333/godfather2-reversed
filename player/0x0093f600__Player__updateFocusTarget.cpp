// FUNC_NAME: Player::updateFocusTarget
void __thiscall Player::updateFocusTarget(int thisPtr, uint param2, uint param3, uint param4, uint param5, uint param6)
{
    uint local_34;
    int local_30;
    uint local_2c;
    uint local_28;
    void (*local_24)();
    uint local_20;
    int local_1c;
    uint local_18;
    uint local_14;
    void (*local_10)();
    uint local_c;
    uint local_8;
    uint local_4;

    local_30 = 0;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    local_34 = 0;
    FUN_004d3d90(param2); // some initialization
    local_20 = 0;
    FUN_004d3d90(param3); // some initialization
    local_4 = param5;
    local_c = param4;
    local_8 = param6;
    // Check if focus target queue (index 0x14) has room versus current count (index 0x1c)
    if (*(int *)(thisPtr + 0x1c) < *(int *)(thisPtr + 0x14)) // +0x1c: mFocusTargetCount, +0x14: mMaxFocusTargets
    {
        FUN_0093f3a0(&local_34); // adds focus target
        FUN_00408680(&DAT_012069c4); // debug/sync
    }
    if (local_1c != 0) // cleanup handlers if set
    {
        (*local_10)(local_1c);
    }
    if (local_30 != 0)
    {
        (*local_24)(local_30);
    }
    return;
}