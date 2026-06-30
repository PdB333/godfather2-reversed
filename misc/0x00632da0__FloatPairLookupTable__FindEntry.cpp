// FUNC_NAME: FloatPairLookupTable::FindEntry
// Address: 0x00632da0
// Role: Searches a fixed-size array (size = 2^exponent) of float-pair-keyed entries backwards.
//       Returns pointer to data (entry->data + 0x10) if an entry with matching keys and type == 4 is found; otherwise 0.
// Input: this (EAX) -> object with a pointer at +0x44 to a table header.
//        key (ESI) -> pointer to a pair of floats (key0, key1).
// Table header layout:
//   +0x07: byte exponent (numEntries = 1 << (exponent & 0x1f))
//   +0x10: pointer to array of entries (each 0x14 bytes)
// Entry layout (size 0x14):
//   +0x00: int type (must be 4 to return)
//   +0x04: int data (returned + 0x10)
//   +0x08: float key0
//   +0x0C: float key1

class FloatPairLookupTable {
public:
    struct Entry {
        int type;   // 0x00
        int data;   // 0x04
        float key0; // 0x08
        float key1; // 0x0C
        // 0x10-0x13: padding
    };

    struct TableHeader {
        char _pad0[7];
        unsigned char exponent; // +0x07
        char _pad1[8];
        Entry* entries; // +0x10
    };

    TableHeader* m_table; // this+0x44

    int* FindEntry(const float* key) {
        int numEntries = 1 << (m_table->exponent & 0x1f); // iVar3 = 1 << (byte at (table+7) & 0x1f)
        if (numEntries != 0) {
            // piVar4 = &entries[numEntries] (one past end)
            // pfVar1 = (float*)(piVar4 + 3) -> points to offset +0xC inside the last entry
            // Loop backwards through all entries
            Entry* cur = &m_table->entries[numEntries]; // piVar4 start
            for (int i = numEntries; i > 0; i--) {
                cur--; // move to previous entry (decrement by 0x14 bytes)
                // piVar4 = cur, pfVar1 = (float*)(cur + 3) -> cur->key1 at offset 0xC? Actually careful:
                // In decompiled: piVar4 starts as &entries[numEntries]. Then inside loop, before decrement, it uses piVar4[-5] etc.
                // So effectively it accesses the entry before the pointer. The decrement happens after the comparison.
                // So we must invert: The first iteration processes entries[numEntries-1].
                // We'll use a while loop that decrements first to avoid off-by-one.
                // Equivalent to:
                // Entry* entry = &entries[numEntries-1]; while (numEntries-- > 0) { ... entry--; }
                // But simpler: start with cur = &entries[numEntries], then in loop: entry = cur-1; then cur--.
                Entry* entry = cur;
                if (*key == entry->key0) {
                    if (*key == 0.0f) {
                        // no key1 check for zero
                    } else {
                        if (key[1] != entry->key1) {
                            continue; // goto LAB_00632e01
                        }
                    }
                    // Also when key0 == 1.0f, fall through to this check (same as default)
                    if (entry->type == 4) {
                        return (int*)(entry->data + 0x10); // piVar4[-4] + 0x10
                    }
                }
                // LAB_00632e01: continue
            }
        }
        return 0;
    }
};