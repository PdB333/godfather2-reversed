// FUNC_NAME: SimObject::updateActions
// Address: 0x0051b120
// Role: Updates a list of action entries, calling virtual update methods and managing flags.
// Reconstructed from Ghidra decompilation.

void SimObject::updateActions() {
    // Check if the updating flag (bit 19, 0x80000) is already set
    uint32_t& flags = *(uint32_t*)(this + 0x0C);
    if ((flags & 0x80000) == 0) {
        // Set updating flag, clear flags at bit 28 (0x10000000) and bit 16 (0x10000)
        flags = (flags & 0x7FF7FFFF) | 0x80000;

        // Number of action entries (signed short at +0x80)
        int16_t numEntries = *(int16_t*)(this + 0x80);
        if (numEntries > 0) {
            // Base of action entry array (each entry is 5 uint32 = 20 bytes, starting at +0xF0)
            uint32_t* entryArray = (uint32_t*)(this + 0xF0);
            for (int i = 0; i < numEntries; i++) {
                uint32_t* entry = entryArray + i * 5; // point to start of current entry

                // Entry layout: [0] = flags, [1] = object pointer, rest unknown
                void* obj = (void*)entry[1];
                void* globalPtr = *(void**)(this + 0x10);

                // If the global pointer is null or the entry's object is null, set the skip flag (bit 28)
                if (globalPtr == nullptr || obj == nullptr) {
                    entry[0] |= 0x10000000;
                } else {
                    // Call virtual function at offset 0x1C on the object (likely an update method)
                    void (*updateFunc)(void*) = (void (*)(void*))(*(void***)obj)[0x1C / 4];
                    updateFunc(obj);
                }
                // Mark the entry as processed (bit 27)
                entry[0] |= 0x8000000;
            }
        }
    }
}