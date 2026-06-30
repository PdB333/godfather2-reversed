// FUN_NAME: Entity::updatePositionRelativeToTarget
void __thiscall Entity::updatePositionRelativeToTarget(int *thisPtr, int targetNodePtr, undefined4 param3)
{
    // local buffer for position (x,y,z) and an 8-byte unknown (maybe for rotation/quaternion)
    float localPos[3];
    undefined1 localRotOrSomething[8];
    undefined4 uStack_4;  // stack junk for debug call
    undefined4 unaff_retaddr; // return address from caller

    // Call virtual function at vtable+0x3c – likely "getLocalPosition" or "getWorldPosition"
    // This fills localPos (float[3]) and localRotOrSomething (perhaps orientation).
    (((void (*)(float *, undefined1 *))(*(int *)(*thisPtr + 0x3c))))(localPos, localRotOrSomething);

    if (targetNodePtr != 0)
    {
        // Get global state (e.g., game manager or player)
        int gameState = FUN_00471610();
        // Adjust local X position relative to target's X and some global offset at +0x38
        localPos[0] = *(float *)(targetNodePtr + 8) + (localPos[0] - *(float *)(gameState + 0x38));
    }

    // Call debug/log function with category 0x40122 (likely "EA" tag)
    FUN_00714f90(uStack_4, &stack0xffffffe0, 0x40122, unaff_retaddr, param3, 0);
    return;
}