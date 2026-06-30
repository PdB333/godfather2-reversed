// FUNC_NAME: Command::enqueueToThreadBuffer

void Command::enqueueToThreadBuffer(Object* slotOwner) {
    // Get current thread's TLS pointer (EA EARS engine per‑thread data)
    // The TIB at FS:0x2c points to the thread local storage base.
    int* threadData = *(int**)(__readfsdword(0x2c));
    int* bufferBase = threadData[2];   // +0x08 = base of per‑thread buffer array

    // Each slot owner has a buffer index stored at offset +0x68
    int slotIndex = *(int*)((char*)slotOwner + 0x68);

    // Compute the start of this slot’s buffer area
    int* slotBuffer = (int*)((char*)bufferBase + 0x4120) + slotIndex; // +0x4120 per slot

    // Read current entry count for this slot (stored at +0x10000 from slot base)
    unsigned int entryCount = *(unsigned int*)((char*)slotBuffer + 0x10000);
    if (entryCount < 0x400) { // maximum 1024 entries per slot
        // Pointer to the next free entry (each entry is 0x40 bytes)
        int* entry = (int*)((char*)slotBuffer + entryCount * 0x40);

        // Increment the slot’s entry count
        *(unsigned int*)((char*)slotBuffer + 0x10000) = entryCount + 1;

        // Store the command object (this) into the entry
        entry[0] = (int)this;                // +0x00: pointer to the command
        // Store a field from the command (probably a type or identifier)
        entry[2] = *(int*)((char*)this + 0x20); // +0x20: e.g. command type

        // Call post‑push processing (e.g. wake up consumer thread)
        FUN_0044e8d0();
    }
}