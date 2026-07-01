// FUNC_NAME: Entity::initFromParentData
void __thiscall Entity::initFromParentData(int thisPtr)
{
    int parentObj = getGlobalData();
    // Copy position/rotation data from global? offsets +0x30, +0x38
    *(int64_t*)(thisPtr + 0x50) = *(int64_t*)(parentObj + 0x30);
    *(int32_t*)(thisPtr + 0x58) = *(int32_t*)(parentObj + 0x38);

    // Resolve base pointer from parent pointer stored at +0x9c (offset 0x48 from actual base)
    int basePtr;
    if (*(int*)(thisPtr + 0x9c) == 0) {
        basePtr = 0;
    } else {
        basePtr = *(int*)(thisPtr + 0x9c) - 0x48;
    }

    // Copy gameplay specific values from base
    *(int32_t*)(thisPtr + 0xcc) = *(int32_t*)(basePtr + 0x2134); // e.g., some state or flag
    *(int32_t*)(thisPtr + 0xd0) = *(int32_t*)(basePtr + 0x1ed0); // another state

    // Also check for a non-zero value at +0x1ed4 in base to copy
    if (*(int32_t*)(basePtr + 0x1ed4) != 0) {
        // Recompute basePtr
        if (*(int*)(thisPtr + 0x9c) == 0) {
            basePtr = 0;
        } else {
            basePtr = *(int*)(thisPtr + 0x9c) - 0x48;
        }
        *(int32_t*)(thisPtr + 0xc8) = *(int32_t*)(basePtr + 0x1ed4); // 0xc8 = 200 decimal
        *(int32_t*)(thisPtr + 0xb0) = getSomeGlobalValue(); // FUN_00806440
    }

    // Additional initialization steps
    staticFunc1();   // FUN_007917b0
    setupChildObjects(thisPtr); // FUN_00792240 (takes this)
    *(uint32_t*)(thisPtr + 0x5c) &= 0xeffeffff; // clear certain flags
    staticFunc2();   // FUN_00790b70
    return;
}