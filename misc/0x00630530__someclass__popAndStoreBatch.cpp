// FUNC_NAME: someclass::popAndStoreBatch
// Address: 0x00630530
// Role: Pops two 8-byte entries from a stack (pointed by this+0x08) and stores each into separately allocated slots.
// The stack stores pairs of ints. Each pop reads two ints from the top, then decrements the stack end pointer by 8.
// Allocation attempts primary pool; if returns sentinel, falls back to secondary allocator.

#include <cstdint>

// Sentinel value indicating slot allocation failure (from primary pool).
extern uint32_t DAT_00e2a93c; // Unknown global

// Primary slot allocator; returns pointer to allocated memory or sentinel on failure.
extern int* allocateSlotPrimary();
// Fallback slot allocator.
extern int* allocateSlotFallback();

class someclass {
public:
    // Offset +0x08: Pointer to the current end of the stack (one past the last entry).
    // Stack entries are 8 bytes (two ints each), growing towards lower addresses (pop decrements end pointer).
    int* pStackEnd;

    void popAndStoreBatch() {
        int* slot;
        int* stackEnd;

        // First pop
        stackEnd = this->pStackEnd;
        slot = allocateSlotPrimary();
        if (slot == (int*)&DAT_00e2a93c) {
            slot = allocateSlotFallback();
        }
        // Copy two ints from the top of the stack
        slot[0] = *(stackEnd - 2); // *(stackEnd - 8) cast to int
        slot[1] = *(stackEnd - 1); // *(stackEnd - 4)
        // Pop by moving stack end down 8 bytes (two ints)
        this->pStackEnd = stackEnd - 2;

        // Second pop
        stackEnd = this->pStackEnd;
        slot = allocateSlotPrimary();
        if (slot == (int*)&DAT_00e2a93c) {
            slot = allocateSlotFallback();
        }
        slot[0] = *(stackEnd - 2);
        slot[1] = *(stackEnd - 1);
        this->pStackEnd = stackEnd - 2;
    }
};