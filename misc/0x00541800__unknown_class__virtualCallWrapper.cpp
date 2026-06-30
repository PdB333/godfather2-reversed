// FUNC_NAME: unknown_class::virtualCallWrapper
void __thiscall unknown_class::virtualCallWrapper(int thisPtr, uint param2, uint param3) {
    // Call a global function (possibly debug/sync)
    FUN_009f2000();

    // Retrieve a pointer at offset 0xd0 from this, then call a virtual function at vtable offset 0x5c
    // vtable entry at index (0x5c / 4) = 0x17
    (*(code **)(*(int *)(thisPtr + 0xd0) + 0x5c))(param2, param3);
    return;
}