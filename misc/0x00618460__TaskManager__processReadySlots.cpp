// FUNC_NAME: TaskManager::processReadySlots
// Function address: 0x00618460
// Reconstructed from Ghidra decompilation. This function iterates through a pool of 4096 task slots,
// checks a bitmap for ready slots (each 64-slot group tracked by a 64-bit mask), and processes
// each ready slot by calling an initialization function (FUN_00618640) and then executing a virtual
// method on a set of objects associated with the slot. It uses a critical section for thread safety
// and maintains a "first free group" counter for efficiency.

#include <windows.h> // For CRITICAL_SECTION, EnterCriticalSection, LeaveCriticalSection

// Forward declaration of the initialization function (address 0x00618640)
void taskSlotInit(uint8_t param[12]);

// Global data (from DAT_...)
// Array of 4096 task slot structures, each 56 bytes (14 ints)
// Base address: 0x011a0f3c
struct TaskSlot {
    int m_objectSingle;          // +0x00: If non-null, single object pointer
    int* m_objectArray;          // +0x04: If m_objectSingle is null, pointer to array of objects
    // ... gap ...
    int m_state;                 // +0x1C (piVar3[7]): state (1=running, 2=waiting?)
    int m_objectCount;           // +0x20 (piVar3[8]): number of objects to process
    // ... remaining fields (non-accessed) ...
    uint8_t m_byteBeforeSlot;    // Actually written at offset -20 from start of slot (see code)
} __attribute__((packed));

// Global bitmap for ready slots, divided into 64-bit groups per 64 slots.
// Two arrays for low and high 32-bit halves. Combined as 64-bit mask per group.
// Addresses: 0x011d8f28 (low), 0x011d8f2c (high)
static uint32_t s_readyBitmapLow[64];   // Low 32 bits of each group
static uint32_t s_readyBitmapHigh[64];  // High 32 bits of each group

// Critical section for thread safety (address 0x011d917c)
static CRITICAL_SECTION s_taskCriticalSection;

// Index of the first group that may have ready slots (address 0x011d9128)
static int s_firstGroupWithReadySlots = 0;

void /*__cdecl*/ TaskManager::processReadySlots(void)
{
    TaskSlot* slotPtr = reinterpret_cast<TaskSlot*>(0x011a0f3c); // Base of slot array
    int currentSlotIndex = 0;             // local_1c
    int remainingSlots = 0x1000;           // local_14, loop counter

    do {
        // Compute the group (uVar2 = currentSlotIndex >> 6) and the 64-bit mask for this slot's bit
        int group = currentSlotIndex >> 6;
        uint64_t slotMask = static_cast<uint64_t>(1) << (currentSlotIndex & 0x3F);
        uint32_t maskLow = static_cast<uint32_t>(slotMask);
        uint32_t maskHigh = static_cast<uint32_t>(slotMask >> 32);

        // Check if the slot's bit is NOT set in the ready bitmap
        bool bitNotSet = ((s_readyBitmapLow[group * 2] & maskLow) == 0) &&
                         ((s_readyBitmapHigh[group * 2] & maskHigh) == 0);
        // Also check the slot's state and that both object pointers are null
        bool slotReady = bitNotSet &&
                         (slotPtr->m_state != 1) &&
                         (slotPtr->m_state != 2) &&
                         (slotPtr->m_objectSingle == 0) &&
                         (slotPtr->m_objectArray == 0);

        if (slotReady) {
            uint8_t initParams[12]; // local_10
            taskSlotInit(initParams); // FUN_00618640

            int objectIndex = 1; // local_18, start at 1 (first object already processed? see below)

            if (slotPtr->m_objectSingle == 0) {
                // Process array of objects
                if (1 < slotPtr->m_objectCount) {
                    do {
                        // Call virtual method at offset 4 on each object in the array
                        int* object = slotPtr->m_objectArray + objectIndex - 1; // index in loop
                        (**(code**)(*(int*)object + 4))(object);
                        objectIndex++;
                    } while (objectIndex < slotPtr->m_objectCount);
                }
            } else {
                // Process single object
                if (1 < slotPtr->m_objectCount) {
                    do {
                        int* object = reinterpret_cast<int*>(slotPtr->m_objectSingle) + objectIndex - 1;
                        (**(code**)(*(int*)object + 4))(object);
                        objectIndex++;
                    } while (objectIndex < slotPtr->m_objectCount);
                }
            }

            // Critical section for bitmap update
            EnterCriticalSection(&s_taskCriticalSection);
            LeaveCriticalSection(&s_taskCriticalSection); // Note: Leave only, no work between?

            // Clear the ready bit for this slot
            s_readyBitmapLow[group * 2] &= ~maskLow;
            s_readyBitmapHigh[group * 2] &= ~maskHigh;

            // Update the first group counter if the current group becomes empty and equals the counter
            if ((group == s_firstGroupWithReadySlots) &&
                (s_readyBitmapLow[group * 2] == 0) &&
                (s_readyBitmapHigh[group * 2] == 0)) {
                s_firstGroupWithReadySlots++;
            }

            // Write a byte (value 2) at offset -20 from the start of the current slot?
            // (This addresses a byte before the slot structure, possibly a shared state or previous slot's field)
            *reinterpret_cast<uint8_t*>(&slotPtr[-5]) = 2; // piVar3 + -5 as byte
        }

        // Advance to next slot
        currentSlotIndex++;
        slotPtr++; // Increment by sizeof(TaskSlot) = 56 bytes (14 ints)
        remainingSlots--;
    } while (remainingSlots != 0);
}