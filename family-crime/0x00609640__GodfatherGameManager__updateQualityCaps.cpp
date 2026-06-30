// FUNC_NAME: GodfatherGameManager::updateQualityCaps
// Address: 0x00609640
// Role: Sets global quality caps (min/max) and calls a virtual method on the global manager (DAT_01205750) with 'this' pointer. The pointer arithmetic (this + param_2) and in_EAX + param_3 are unused except for the call; their values are dead.

void __thiscall GodfatherGameManager::updateQualityCaps(int param_2, int param_3)
{
    int local_10[2];
    local_10[0] = reinterpret_cast<int>(this); // pass this pointer as array

    // Virtual call on global object at *DAT_01205750, vtable offset 300 (index 75)
    ((void (__thiscall *)(void*, int*))(*(void***)DAT_01205750)[75])(DAT_01205750, local_10);

    // Clamp global minimum cap
    if (DAT_012058d4 < 0xae)
        DAT_012058d4 = 0xae;

    // Set global flag to enable feature
    DAT_011f3c90 = 1;

    // Clamp global maximum cap (only if it exceeds 0xae)
    if (0xae < DAT_00f1598c)
        DAT_00f1598c = 0xae;
}