// FUNC_NAME: RandomPool::pickRandomUnusedSlot
// Purpose: Given a pool with a count and a bitmask of used slots,
// randomly picks an unused slot, marks it used, and returns the index.
// If all slots are used, resets the used mask.
// The pool structure is assumed to have:
// +0x10: uint16 count (max 16 slots)
// +0x12: uint16 usedMask (bitmask of used slots)

#include <cstdlib>
#include <cmath>

// Global constant from decompilation (likely 1.0f / RAND_MAX)
extern const float g_randScale; // DAT_00e44590

struct RandomPool {
    // ... other fields (0x00..0x0F) ...
    uint16_t count;      // +0x10
    uint16_t usedMask;   // +0x12
    // ... other fields ...
};

int __fastcall RandomPool::pickRandomUnusedSlot(RandomPool* thisPtr)
{
    uint32_t uVar4 = 0;
    uint16_t uVar3 = 0;
    uint32_t uVar7 = 0;

    // Build a mask of all bits from 0 to count-1
    if (thisPtr->count != 0) {
        do {
            uint8_t bitIndex = (uint8_t)uVar7;
            uVar7++;
            uVar4 |= (1U << (bitIndex & 0x1F));
            uVar3 = (uint16_t)uVar4; // mask after each iteration
        } while (uVar7 < thisPtr->count);
    }

    // If all slots are used (mask matches), clear the used mask
    if (uVar3 == (uVar3 & thisPtr->usedMask)) {
        thisPtr->usedMask = 0;
    }

    // No slots available
    if (thisPtr->count == 0) {
        return 0;
    }

    int randVal = rand();
    // Scale rand to range [0, count)
    float scaled = (float)randVal * g_randScale * (float)thisPtr->count;
    int candidate = (int)round(scaled); // rounding may be implementation-specific

    // If candidate is already used, find the next free slot
    if ((thisPtr->usedMask & (1U << (candidate & 0x1F))) != 0) {
        do {
            // Wrap around using modulo count
            candidate = (candidate + 1) % (uint32_t)thisPtr->count;
        } while ((thisPtr->usedMask & (1U << (candidate & 0x1F))) != 0);
    }

    // Mark the selected slot as used
    thisPtr->usedMask |= (1U << (candidate & 0x1F));
    return candidate;
}