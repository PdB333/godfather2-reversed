// FUNC_NAME: SomeManager::constructor
void __fastcall SomeManager::constructor(SomeManager* this) {
    uint32_t* data = reinterpret_cast<uint32_t*>(this);
    uint32_t globalValue = DAT_00e2b1a4; // Some global singleton pointer

    // VTable setup
    data[0] = reinterpret_cast<uint32_t>(&PTR_FUN_00e39c48);

    // Self-referencing pointer (likely internal linked list or buffer start)
    data[4] = reinterpret_cast<uint32_t>(&data[8]);

    // Flags or type info
    data[6] = 0x80000008;

    // Initialize 8 slots (each 24 words = 96 bytes)
    // Each slot has a pointer, two -1 sentinels, and two zeros
    for (int i = 0; i < 8; i++) {
        int base = 12 + i * 24; // Word offset of slot start
        data[base] = globalValue;        // +0x00 in slot: link/pointer
        data[base + 1] = 0xFFFFFFFF;     // +0x04: sentinel -1
        data[base + 2] = 0xFFFFFFFF;     // +0x08: sentinel -1
        data[base + 3] = 0;              // +0x0C: zero
        data[base + 4] = 0;              // +0x10: zero
    }

    // Additional initialization for first element? (overwritten later)
    data[0x0C] = globalValue; // Already set in loop, but explicit here
    data[0x0D] = 0xFFFFFFFF;
    data[0x10] = 0xFFFFFFFF;
    data[0x18] = 0;
    data[0x1C] = 0;

    // Repeat pattern for remaining slots (all covered by loop)
    // Explicit sets for slots 2-8 (indices 0x24, 0x3C, ..., 0xB4) are redundant

    // Set slot count? (index 5 is used for something else)
    data[5] = 0; // Possibly count or index

    // Last assignment: set first word again to global (index 1)
    data[1] = globalValue;
}