// FUNC_NAME: registerStreamCallbacks
void registerStreamCallbacks(void)
{
    uint32 result;
    int *currentVtablePtr;
    byte *entryFlagPtr;
    uint32 entryIndex;
    uint32 newEntryFlag;

    // Call virtual method at offset 4 on the global manager object
    result = (*(code **)(DAT_0121a1f0 + 4))();
    // Convert result to some ID/handle
    _DAT_0121a1f8 = someHashFunction(result);
    // Call virtual method at offset 0x10 on the same object (likely init)
    (**(code **)(DAT_0121a1f0 + 0x10))();
    // Store a copy of the global pointer
    _DAT_0121a1f4 = DAT_012058ec;
    // Increment a global counter (used as unique ID)
    DAT_012058f8 = DAT_012058f8 + 1;
    // Set the new counter value into another global
    _DAT_0121a1fc = DAT_012058f8;

    // Manipulate a vtable pointer at offset 0x14 of some global structure
    currentVtablePtr = (int *)(DAT_01206880 + 0x14);
    // Set the vtable to a static table of function pointers
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01125070;
    // Advance the vtable pointer (increase object size? Or register next slot)
    *currentVtablePtr = *currentVtablePtr + 4;
    // Store the address of the global manager object into another global
    DAT_012058ec = &DAT_0121a1f0;

    // Build the flag for the new entry: low byte = 0x80, rest from uStack_4 initial value
    newEntryFlag = CONCAT31(uStack_4._1_3_, 0x80);

    // Validate existing entries: flag must be <= 0x80
    if (DAT_012224a8 != 0) {
        entryFlagPtr = &DAT_01222330;
        entryIndex = 0;
        do {
            if (0x80 < *entryFlagPtr) {
                errorHandler();
                return;
            }
            entryIndex = entryIndex + 1;
            entryFlagPtr = entryFlagPtr + 0xc; // 12-byte stride
        } while (entryIndex < DAT_012224a8);
    }

    // Add new entry if table not full (max 32 entries)
    if (DAT_012224a8 < 0x20) {
        // Write two function pointers (0x00505b10 and 0x00505b20) into the entry
        *(undefined8 *)(&DAT_01222328 + DAT_012224a8 * 3) = 0x505b2000505b10;
        // Write the flag (with 0x80 low byte) into the entry's last 4 bytes
        *(undefined4 *)(&DAT_01222330 + DAT_012224a8 * 0xc) = newEntryFlag;
        DAT_012224a8 = DAT_012224a8 + 1;
    }

    return;
}