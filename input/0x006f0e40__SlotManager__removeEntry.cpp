// FUNC_NAME: SlotManager::removeEntry
void __thiscall SlotManager::removeEntry(int thisPtr, int entryId)
{
    // The class has an array of 2 slots at offset 0x30.
    // Each slot is 32 bytes (0x20), with fields:
    //   -4: ownerPtr
    //   +0: id
    //   +4: flags (treated as byte)
    //   +8: resourcePtr
    //   +12: cleanupArg
    // Offsets are relative to the slot's base pointer (piVar2).
    int* slotBase = (int*)(thisPtr + 0x30);
    int slotCount = 2;

    do {
        if (*slotBase == entryId) {
            // Check conditions before cleanup:
            // ownerPtr != 0, flags has bit 0x20 set, and resourcePtr != 0
            if ((slotBase[-1] != 0) && ((*(byte*)(slotBase + 4) & 0x20) != 0) && (slotBase[2] != 0)) {
                releaseResource(slotBase[3]); // FUN_00815060
            }
            // Clear the entire slot (5 ints: owner, id, flags, resource, cleanup)
            *slotBase = 0;
            slotBase[1] = 0;
            slotBase[-1] = 0;
            slotBase[2] = 0;
            slotBase[3] = 0;
        }
        slotBase += 8; // advance to next slot (8 ints = 32 bytes)
        slotCount--;
    } while (slotCount != 0);
}