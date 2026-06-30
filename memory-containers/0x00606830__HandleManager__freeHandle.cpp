// FUNC_NAME: HandleManager::freeHandle
// Function address: 0x00606830
// Role: Frees a handle/slot in a fixed-size handle table (0x1000 entries, each 0x38 bytes).
// Uses a 64-bit bitmap (two 32-bit words per 64-slot group) to track free slots.
// The handle table is at g_handleTable, bitmap at g_handleBitmap, next free hint at g_nextFreeHint.
// Critical section g_handleCriticalSection protects bitmap updates.
// The function validates the resource pointer against the handle table entry before freeing.

#include <windows.h> // For CRITICAL_SECTION, EnterCriticalSection, LeaveCriticalSection

// Handle table entry structure (size 0x38)
struct HandleEntry {
    byte state;          // +0x00: state (2=in use, 3=free)
    byte field_1;        // +0x01: some byte field
    short field_2;       // +0x02: some short field
    short field_4;       // +0x04: some short field
    // ... remaining 0x38-6 bytes unknown
};

// Global data (from DAT_011a0f28, DAT_011d8f28, DAT_011d8f2c, DAT_011d9128, DAT_011d917c)
static HandleEntry g_handleTable[0x1000];          // +0x00 each entry 0x38 bytes
static uint32_t g_handleBitmap[0x1000 / 64 * 2];  // Two 32-bit words per 64-slot group (DAT_011d8f28 and DAT_011d8f2c)
static uint32_t g_nextFreeHint;                    // DAT_011d9128: next group to search for free slots
static CRITICAL_SECTION g_handleCriticalSection;   // DAT_011d917c

// __allshl() is a 64-bit left shift; we use uint64_t for clarity
static inline uint64_t shiftLeft64(uint32_t shift) {
    return (uint64_t)1 << shift;
}

void HandleManager::freeHandle(uint32_t index, void* resourcePtr) {
    HandleEntry* entry;
    uint32_t group;
    uint64_t bitMask;

    // If index is valid (< 0x1000), get pointer to the handle table entry
    if (index < 0x1000) {
        entry = &g_handleTable[index];
    } else {
        entry = nullptr;
    }

    // Compare the original index with the index passed in EAX? 
    // Actually the decompiler shows param_1 (index) and in_EAX (another index) being compared.
    // This is likely a bug in decompilation; we assume the function takes one index.
    // The logic below uses 'index' as the handle to free.

    // If the resource pointer is provided, validate it against the table entry
    if (resourcePtr != nullptr) {
        // Compare fields at offsets +1, +2, +4
        if (entry != nullptr &&
            *(short*)((uint8_t*)resourcePtr + 2) == entry->field_2 &&
            *(short*)((uint8_t*)resourcePtr + 4) == entry->field_4 &&
            *((uint8_t*)resourcePtr + 1) == entry->field_1) {
            // Match: mark entry as free (state=3)
            entry->state = 3;
        } else {
            // No match: mark entry as invalid (state=2)
            entry->state = 2;
        }
    } else {
        // No resource pointer: mark entry as free directly
        if (index < 0x1000) {
            g_handleTable[index].state = 3;
        } else {
            // Invalid index; this path is likely unreachable
            *(uint8_t*)0 = 3; // Bug in original code? Ignore.
        }
    }

    // Clear the bit in the bitmap for this index
    group = index >> 6; // 64 slots per group
    bitMask = shiftLeft64(index & 0x3F);

    EnterCriticalSection(&g_handleCriticalSection);
    // Clear the bit in the two 32-bit words (low and high parts of 64-bit mask)
    g_handleBitmap[group * 2] &= ~(uint32_t)bitMask;
    g_handleBitmap[group * 2 + 1] &= ~(uint32_t)(bitMask >> 32);
    LeaveCriticalSection(&g_handleCriticalSection);

    // Update next free hint if this group becomes completely free
    if (group == g_nextFreeHint &&
        g_handleBitmap[group * 2] == 0 &&
        g_handleBitmap[group * 2 + 1] == 0) {
        g_nextFreeHint++;
    }
}