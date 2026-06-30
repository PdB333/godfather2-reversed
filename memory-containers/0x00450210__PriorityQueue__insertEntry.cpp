// FUNC_NAME: PriorityQueue::insertEntry
struct PriorityEntry {
    float data0;   // +0x00
    float data1;   // +0x04
    float data2;   // +0x08
    float data3;   // +0x0C
    float priority; // +0x10
    int32_t flags;  // +0x14
    float pad[2];   // +0x18 (unused)
};

struct PriorityList {
    PriorityEntry entries[4]; // +0x00
    uint32_t count;           // +0x98
    // total size: 0x9C
};

extern float g_defaultPriority; // DAT_00e2b05c
extern float g_scale;           // DAT_00e4461c

uint32_t insertPriorityEntry(PriorityList* list, int32_t* data, int32_t flags, float newPriority, uint32_t eaxValue) {
    if ((flags == 0) && (newPriority != g_defaultPriority)) {
        // Early return with packed status bits
        // in_EAX high byte and comparison flags
        return (uint32_t)((short)(eaxValue >> 16)) << 8 |
               ((newPriority == g_defaultPriority) << 6) |
               ((isnan(newPriority) || isnan(g_defaultPriority)) << 2) |
               2U |
               (newPriority < g_defaultPriority);
    }

    uint32_t count = list->count;
    uint32_t insertIdx = 0;

    float* entryFloats = (float*)&list->entries[0]; // cast for pointer arithmetic
    do {
        if (count <= insertIdx) break;

        PriorityEntry* pEntry = (PriorityEntry*)((uint8_t*)list + insertIdx * 0x20);
        float computed = (pEntry->data0 + pEntry->data1 + pEntry->data2) * pEntry->priority * g_scale;
        if (computed < newPriority) {
            // Found insertion point
            break;
        }
        insertIdx++;
    } while (insertIdx < 4);

    if (insertIdx >= count && count < 4) {
        // Append at end
        // fall through to insertion
    } else if (count >= 4) {
        // List full, fail
        return insertIdx & 0xFFFFFF00;
    }

    // Now insert at insertIdx (or append)
    uint32_t result = (insertIdx >> 8) | 0x100; // CONCAT31 magic? Actually CONCAT31((int3)(insertIdx >> 8),1) sets byte 0 to 1
    uint32_t temp = (insertIdx >> 8); // lower 24 bits?
    result = (temp << 8) | 0x1; // approximate: set low byte to 1, preserve high 24 bits

    if (count != 0) {
        if (count > 3) count = 3; // clamp to 3 for shift
        if (insertIdx + 1 <= count) {
            // Shift entries right by one from insertIdx to count
            int numToMove = count - insertIdx;
            PriorityEntry* src = &list->entries[count];
            PriorityEntry* dst = &list->entries[count - 1];
            for (int i = 0; i < numToMove; i++) {
                // Copy 4 qwords (32 bytes) per entry: using 8-byte moves
                __int64* qwSrc = (__int64*)src;
                __int64* qwDst = (__int64*)dst;
                qwDst[0] = qwSrc[-4];
                qwDst[1] = qwSrc[-3];
                qwDst[2] = qwSrc[-2];
                qwDst[3] = qwSrc[-1];
                src--;
                dst--;
            }
        }
    }

    // Insert new entry at insertIdx
    PriorityEntry* newEntry = &list->entries[insertIdx];
    newEntry->data0 = *(float*)&data[0];
    newEntry->data1 = *(float*)&data[1];
    newEntry->data2 = *(float*)&data[2];
    newEntry->data3 = *(float*)&data[3];
    newEntry->priority = newPriority;
    newEntry->flags = flags;

    if (list->count < 4) {
        list->count++;
    }
    return result;
}