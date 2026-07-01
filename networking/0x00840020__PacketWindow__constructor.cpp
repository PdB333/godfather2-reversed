// FUNC_NAME: PacketWindow::constructor
undefined4* __thiscall PacketWindow::constructor(undefined4* thisPtr, undefined4 param) {
    int i;
    undefined4* slotPtr;

    // Initialize base or sub-object with the given parameter (likely a size or ID)
    FUN_0083f8e0(param);

    // Set virtual function table pointers
    *thisPtr = &PTR_FUN_00d74574;                 // main vtable
    thisPtr[0xf] = &PTR_LAB_00d74564;            // secondary vtable (maybe for packet handling)
    thisPtr[0x12] = &PTR_LAB_00d74560;            // tertiary vtable

    // Step 1: Fill 20 slot entries with a magic sentinel (0xfe16702f)
    // Each slot occupies 2 int32_t words (8 bytes)
    slotPtr = thisPtr + 0x17;                     // start of slot array
    for (i = 0; i < 20; i++) {
        *slotPtr = 0xfe16702f;                    // magic number (invalid/free marker)
        slotPtr += 2;                             // move to next slot's first word
    }

    // Step 2: Initialize a secondary counter/parameter with 0x14 (20)
    FUN_0083f970(0x14);

    // Step 3: Properly initialize each slot pair: first word = 0 (reset), second = 0xffffffff (invalid sequence)
    slotPtr = thisPtr + 0x18;                     // start at second word of first slot
    for (i = 0; i < 20; i++) {
        slotPtr[-1] = 0;                          // write 0 to first word of slot (overwrites magic)
        *slotPtr = 0xffffffff;                    // write invalid sequence indicator to second word
        slotPtr += 2;                             // advance to next slot's second word
    }

    return thisPtr;
}