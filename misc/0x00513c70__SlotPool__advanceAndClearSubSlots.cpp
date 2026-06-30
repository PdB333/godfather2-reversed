// FUNC_NAME: SlotPool::advanceAndClearSubSlots
// Address: 0x00513c70
// This function advances to the next slot in a linked list pool, clears 8 sub-slots (each 0x50 bytes) in the current slot,
// and returns the offset of the current slot and a success flag via an output pair.
// The object (this) is passed in EAX. The function uses a thread-local global pool manager (via FS:0x2c)

#include <stdint.h>

// Structure for the output pair (offset + success flag)
struct SlotResult {
    uint32_t offset;   // [0] offset into pool base
    uint32_t success;  // [1] nonzero if a slot was obtained
};

// The thread-local pool manager structure (accessed via FS:0x2c)
struct PoolManager {
    void* basePtr;      // +0x00: pointer to some base (used in offset calc)
    // offset +0x08: another base address (added to this->firstField)
    uint32_t baseOffset; // +0x08: actually an int, used as base
};

// The SlotPool object structure (this)
struct SlotPool {
    uint32_t firstField;   // +0x00: used as an offset/adjustment
    // ... other fields up to index 5
    int32_t currentIndex;  // +0x14 (index 5): current slot index in the linked list
    int32_t count;         // +0x18 (index 6): number of slots remaining
    int32_t minCount;      // +0x1c (index 7): minimum count seen
    void* overflowCallback; // +0x20 (index 8): fallback callback pointer (vtable)
};

// Helper to read TLS pointer at FS:0x2c
inline PoolManager* getTlsPoolManager() {
    void* ptr;
    __asm {
        mov eax, fs:[0x2c]
        mov ptr, eax
    }
    return (PoolManager*)ptr;
}

struct SlotResult* __thiscall SlotPool_advanceAndClearSubSlots(SlotPool* thisPtr, SlotResult* outResult) {
    int32_t currentIdx = thisPtr->currentIndex; // in_EAX[5]
    PoolManager* mgr = getTlsPoolManager(); // piVar1 from FS:0x2c

    if (currentIdx != -1) {
        uint32_t baseAdjust = 0;
        if (thisPtr->firstField != 0) {
            baseAdjust = mgr->baseOffset + thisPtr->firstField;
        }
        uint32_t slotBase = currentIdx * 0x2a0 + baseAdjust; // iVar4

        int32_t slotOffset; // iVar5
        if (slotBase == 0) {
            slotOffset = 0;
        } else {
            slotOffset = slotBase - mgr->baseOffset; // iVar5 = slotBase - baseOffset
        }

        // Read next index from current slot at mgr->basePtr+8 + slotOffset
        int32_t nextIndex = *(int32_t*)(slotOffset + *(int32_t*)((uint32_t)mgr->basePtr + 8));

        // Decrement count and update current index
        thisPtr->count--;
        thisPtr->currentIndex = nextIndex;

        // Update minCount if necessary
        if ((uint32_t)thisPtr->count < (uint32_t)thisPtr->minCount) {
            thisPtr->minCount = thisPtr->count;
        }

        // If slotOffset is nonzero, clear the 8 sub-slots (each 0x50 bytes, first int set to 0)
        if (slotOffset != 0) {
            void* slotPtr = (char*)mgr->basePtr + 8 + slotOffset; // iVar3 = basePtr+8 + slotOffset
            if (slotPtr != nullptr) {
                // Clear the first 4 bytes of each sub-slot
                *(uint32_t*)((char*)slotPtr + 0x50) = 0;
                *(uint32_t*)((char*)slotPtr + 0xa0) = 0;
                *(uint32_t*)((char*)slotPtr + 0xf0) = 0;
                *(uint32_t*)((char*)slotPtr + 0x140) = 0;
                *(uint32_t*)((char*)slotPtr + 0x190) = 0;
                *(uint32_t*)((char*)slotPtr + 0x1e0) = 0;
                *(uint32_t*)((char*)slotPtr + 0x230) = 0;
                *(uint32_t*)((char*)slotPtr + 0x280) = 0;
            }
        }

        outResult->success = (slotBase != 0) ? 1 : 0;
        outResult->offset = (uint32_t)slotOffset;
        return outResult;
    }
    // currentIndex == -1 => fallback to callback if set, else null result
    if (thisPtr->overflowCallback != nullptr) {
        // Call virtual method at vtable+4
        (*(void(__thiscall**)(SlotPool*, SlotResult*))(*(uint32_t*)thisPtr->overflowCallback + 4))(thisPtr, outResult);
        return outResult;
    }
    outResult->offset = 0;
    outResult->success = 0;
    return outResult;
}