// FUNC_NAME: SlotPool::allocateFromSlotPool
// Address: 0x006157d0
// This function allocates a 24-byte slot from a fixed-size global pool.
// It uses a mutex (at 0x00e2ac20) for thread safety.
// Returns pointer to allocated slot (first 4 bytes set to 1) or NULL if pool full.

#include <cstddef>

// External lock/unlock functions (likely critical section enter/leave)
extern void poolLock(void* mutex);
extern void poolUnlock(void* mutex);

// Global pool parameters (from Ghidra data references)
#define POOL_BASE      ((int*)0x01222574)   // base of slot array
#define POOL_END       ((int*)0x0122312c)   // end address (exclusive)
#define SLOT_SIZE_INTS  6                   // each slot is 6 ints (24 bytes)
#define SLOT_COUNT      ((POOL_END - POOL_BASE) / SLOT_SIZE_INTS)

// Mutex address
#define POOL_MUTEX      ((void*)0x00e2ac20)

// Allocate a slot from the pool.
// Returns pointer to the allocated slot (first int set to 1) or NULL on failure.
void* allocateFromSlotPool()
{
    poolLock(POOL_MUTEX);

    int* current = POOL_BASE;
    int index = 0;

    // Linear scan for a free slot (first int == 0)
    while (current < POOL_END)
    {
        if (*current == 0)
        {
            // Found free slot; compute pointer to start of slot
            int* slotPtr = POOL_BASE + (index * SLOT_SIZE_INTS);
            // Note: slotPtr is always non-null because POOL_BASE is a fixed address,
            // but Ghidra shows a null check which we preserve for consistency.
            if (slotPtr == nullptr)
            {
                poolUnlock(POOL_MUTEX);
                return nullptr;
            }

            // Mark as allocated (first int = 1)
            *slotPtr = 1;

            poolUnlock(POOL_MUTEX);
            return slotPtr;
        }

        // Move to next slot
        current += SLOT_SIZE_INTS;
        index++;
    }

    // No free slot found
    poolUnlock(POOL_MUTEX);
    return nullptr;
}