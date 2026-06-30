// FUNC_NAME: AllocatePoolEntry
// Address: 0x00568fb0
// Allocates a slot from a fixed-size pool of structures (size = 0x150 bytes each).
// Searches for first free slot (inUse == 0), zeros its fields, marks it as used, returns pointer to it.
// Returns nullptr if no free slot available.

struct PoolEntry {
    int field_0;        // +0x00
    int field_4;        // +0x04
    // padding to +0x108
    int field_108;      // +0x108
    int field_10c;      // +0x10c
    int field_120;      // +0x120
    int inUse;          // +0x128 — flag: 0 = free, 1 = used
};

static PoolEntry g_pool[64]; // at DAT_0121c050, each entry 0x150 bytes, total 0x5400 bytes

PoolEntry* AllocatePoolEntry()
{
    uint byteOffset = 0;
    int slotIndex = 0;

    do {
        // Check if the flag at offset +0x128 is zero (free slot)
        if (g_pool[slotIndex].inUse == 0) {
            // Zero out all fields before marking as used
            g_pool[slotIndex].field_0   = 0;
            g_pool[slotIndex].field_4   = 0;
            g_pool[slotIndex].field_108 = 0;
            g_pool[slotIndex].field_10c = 0;
            g_pool[slotIndex].field_120 = 0;
            g_pool[slotIndex].inUse     = 1;
            return &g_pool[slotIndex];
        }

        byteOffset += 0x150;
        slotIndex++;
    } while (byteOffset < 0x5400);

    return nullptr;
}