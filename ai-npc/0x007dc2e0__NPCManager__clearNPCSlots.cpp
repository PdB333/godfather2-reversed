// FUNC_NAME: NPCManager::clearNPCSlots
void __fastcall NPCManager::clearNPCSlots(int this) {
    int activeCount = *(int *)(this + 0xa00); // +0xa00: number of active NPC slots
    if (activeCount == 0) {
        *(int *)(this + 0xa00) = 0;
        return;
    }
    if (activeCount != 1) {
        int *slotPtr = (int *)(this + 8); // +0x08: start of NPC slot array (each slot = 40 bytes)
        unsigned int index = 0;
        do {
            // Release the NPC object if present
            if (*slotPtr != 0) {
                destroyNPC(slotPtr); // FUN_004daf90 - releases the NPC object and clears the pointer
            }
            // Reset slot metadata
            // The slot structure is 40 bytes, with vtable pointer at offset -8 relative to the NPC pointer
            slotPtr[-2] = (int)&PTR_LAB_00e2f0c0; // Placeholder vtable
            // Condition likely checks if this is not the first slot (index != 0)
            if (slotPtr != (int *)&DAT_00000008) { // Decompiler artifact; actually compares to start of array
                slotPtr[-2] = (int)&PTR_FUN_00d5dbbc; // Base vtable for empty slot
                slotPtr[-1] = -1;      // +0x04: some state or ID
                *slotPtr = 0;          // +0x08: NPC pointer
                slotPtr[1] = 0;        // +0x0C: other field
                *(uint8_t *)(slotPtr + 5) = 0; // +0x1C: byte field
                slotPtr[2] = 0;        // +0x10
                slotPtr[3] = 0;        // +0x14
                slotPtr[4] = 0;        // +0x18
                slotPtr[6] = DAT_01205228; // +0x20: global constant
                slotPtr[7] = DAT_00d5ccf8; // +0x24: another global constant
            }
            index++;
            slotPtr += 10; // Advance to next slot (10 ints = 40 bytes)
        } while (index < activeCount - 1U);
        *(int *)(this + 0xa00) = 0;
        return;
    }
    *(int *)(this + 0xa00) = 0;
}