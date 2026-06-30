// FUNC_NAME: PacketQueue::addEntry
// Address: 0x005e9380
// Reconstructed from Ghidra decompilation of The Godfather 2 (2008, EA EARS engine)
// Role: Adds an entry to a fixed-size circular buffer (4 slots). After the buffer is full,
//       the most recent slot is overwritten (ring behavior with writeIndex always 0, so slot 3 is overwritten).
//       Returns a pointer to the entry with its lowest byte set to 1 (success flag).

#define MAX_QUEUE_ENTRIES 4
#define ENTRY_SIZE_BYTES 0x78   // 120 bytes

struct PacketEntry {
    uint32_t field_00;            // +0x00: first data word (param_3)
    uint32_t data[27];            // +0x04 to +0x6C: 27 dwords copied from param_4
    uint32_t field_1C;            // +0x70 (offset 0x1C dwords): param_5
    uint32_t field_1D;            // +0x74 (offset 0x1D dwords): copy from queue->field_48C
};

struct PacketQueue {
    int32_t count;                // +0x1FC: number of entries written (capped at 4)
    int32_t writeOffset;          // +0x200: always 0 after init, used in calculations
    uint32_t field_48C;           // +0x48C: some value copied into each new entry
    PacketEntry entries[4];       // +0x294: array of 4 entries, each 0x78 bytes
};

// __fastcall: ECX = unused, EDX = queue pointer
// For __thiscall, this would be the queue, but the decompiler shows param_2 as the struct.
// We treat it as a static method on PacketQueue, receiving the queue pointer as arg1 (EDX).
// Since ECX is unused, it might be a relic of fastcall convention or an optimizer trick.
PacketEntry* __fastcall PacketQueue_addEntry(
    void* unusedECX,             // ECX, unused
    PacketQueue* queue,          // EDX = pointer to the queue
    uint32_t param3,
    uint32_t* param4,            // pointer to 27 dwords to copy
    uint32_t param5)
{
    int32_t count = queue->count;
    int32_t newIndex;

    if (count < 1) {
        // First entry: reset writeOffset to 0, count becomes 1
        queue->writeOffset = 0;
        queue->count = 1;
        newIndex = 0; // will be computed below? Actually the code recalculates after this branch, but sets count and offset explicitly.
    }
    else if (count < 4) {
        // Not full yet: new index = writeOffset + count, wrap modulo 4 if >3
        newIndex = queue->writeOffset + count;
        if (newIndex > 3) {
            newIndex -= 4;
        }
        queue->count = count + 1;
    }
    else {
        // Buffer full (count >= 4): overwrite the oldest entry? Actually the code uses writeOffset - 1 + count,
        // but writeOffset is always 0 so it becomes count-1, which is slot 3 (the most recent).
        // This effectively overwrites the newest entry each time.
        newIndex = queue->writeOffset - 1 + count;
        if (newIndex > 3) {
            newIndex -= 4;
        }
        // count remains 4
    }

    // Compute address of the entry slot
    PacketEntry* entry = &queue->entries[newIndex];

    // Fill entry fields
    entry->field_00 = param3;                                 // first dword
    entry->field_1C = param5;                                 // at offset 0x1C dwords
    // Copy 27 dwords from param4 into entry->data[0..26]
    for (int i = 0; i < 27; i++) {
        entry->data[i] = param4[i];
    }
    entry->field_1D = queue->field_48C;                       // copy from queue struct

    // Return pointer to entry with low byte set to 1 (success indicator)
    return (PacketEntry*)(((uint32_t)entry & 0xFFFFFF00) | 1);
}