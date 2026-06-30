// FUNC_NAME: HashTable::findInsertIndex
// Address: 0x00499100
// Searches for the insertion point of a float key in a hash table with linear probing.
// Uses global probing index and mask for slot mapping.
// Returns the index where the key should be inserted (first slot where key <= stored key).

#include <cstdint>

// Global state for probing
extern uint32_t g_probeIndex;       // DAT_012054b4 - current probe position
extern uint32_t g_tableMask;        // DAT_010c2678 - mask to compute slot index
extern float    g_tableSlots[];     // DAT_010c2680 - array of stored keys

struct SearchInfo {
    uint32_t baseCount;   // +0x04 - some base count offset
    uint32_t capacity;    // +0x08 - maximum number of elements to consider
    float    key;         // +0x0C - key to insert
};

uint32_t __fastcall HashTable::findInsertIndex(void* /*unused*/, SearchInfo* info) {
    uint32_t probeIdx = g_probeIndex;
    uint32_t effectiveCount = info->baseCount + 2; // Why +2? Possibly header adjustment
    if (info->capacity < effectiveCount) {
        effectiveCount = info->capacity;
    }

    uint32_t resultIdx = 0;

    // Process in blocks of 4 (unrolled loop)
    if (effectiveCount > 3) {
        do {
            // Check first slot in block (probeIdx)
            if (info->key <= g_tableSlots[g_tableMask & probeIdx]) {
                g_probeIndex = probeIdx + 1;
                return resultIdx;
            }
            g_probeIndex = probeIdx + 2;

            // Check second slot
            if (info->key <= g_tableSlots[g_tableMask & (probeIdx + 1)]) {
                return resultIdx + 1;
            }
            g_probeIndex = probeIdx + 3;

            // Check third slot
            if (info->key <= g_tableSlots[g_tableMask & (probeIdx + 2)]) {
                return resultIdx + 2;
            }
            probeIdx += 4;
            g_probeIndex = probeIdx;

            // Check fourth slot (note: slot at probeIdx+3 is skipped intentionally?)
            if (info->key <= g_tableSlots[g_tableMask & g_probeIndex]) {
                g_probeIndex = probeIdx; // redundant but matches binary
                return resultIdx + 3;
            }
            resultIdx += 4;
            g_probeIndex = probeIdx;
        } while (resultIdx < effectiveCount - 3);
    }

    // Tail loop for remaining 0–3 elements
    while (resultIdx < effectiveCount) {
        uint32_t slotIdx = g_tableMask & g_probeIndex;
        g_probeIndex = g_probeIndex + 1;
        if (info->key <= g_tableSlots[slotIdx]) {
            break;
        }
        resultIdx++;
    }

    return resultIdx;
}