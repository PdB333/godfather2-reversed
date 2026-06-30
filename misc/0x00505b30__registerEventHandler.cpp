// FUNC_NAME: registerEventHandler
void registerEventHandler(void)
{
    // Call virtual functions on global manager object (DAT_0121a1f0 points to vtable)
    int initResult = (*(int (__thiscall **)(void))(*(int *)DAT_0121a1f0 + 4))();          // +0x4
    g_someValue = FUN_0060d740(initResult);
    (*(void (__thiscall **)(void))(*(int *)DAT_0121a1f0 + 0x10))();                      // +0x10

    // Global state update
    g_managerPtr = DAT_012058ec;            // Store previous manager pointer
    g_counter = DAT_012058f8 + 1;           // Increment global counter
    DAT_012058f8 = g_counter;

    // Adjust a vtable pointer at offset +0x14 in global structure at DAT_01206880
    int* vtablePtrSlot = *(int**)(DAT_01206880 + 0x14);
    *vtablePtrSlot = (int)&PTR_LAB_01125070; // Set to new vtable
    *(int*)(DAT_01206880 + 0x14) = vtablePtrSlot + 1; // Advance pointer

    // Set up new manager reference
    DAT_012058ec = &DAT_0121a1f0;
    g_otherCounter = DAT_012058f8;          // Set to the just-incremented counter

    // Prepare the flag byte for new handler entry
    uint flagValue = 0x80;                  // Actually constructed from stack garbage, but we set to 0x80

    // Validate existing handlers: if any first byte > 0x80, call error and return
    if (g_handlerCount != 0) {
        byte* handlerArray = &g_handlerList[0]; // DAT_01222330
        for (uint i = 0; i < g_handlerCount; i++) {
            if (*handlerArray > 0x80) {        // Check first byte of each 12-byte entry
                FUN_00609bf0();
                return;
            }
            handlerArray += 12;                 // Each entry is 0xC bytes
        }
    }

    // Add new handler entry if under maximum (0x20)
    if (g_handlerCount < 0x20) {
        int index = g_handlerCount;
        // Write 8 bytes: two function pointers (order: low 4 bytes = 0x00505b10, high = 0x00505b20)
        *(uint64*)((byte*)g_handlerBase + index * 3) = 0x00505b2000505b10; // Byte offset base + count*3
        // Write 4 bytes: flag value (0x80)
        *(uint*)(&g_handlerList[index]) = flagValue;                       // Offset base+8 + count*12
        g_handlerCount++;
    }
}