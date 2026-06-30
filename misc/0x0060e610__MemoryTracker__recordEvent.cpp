// FUNC_NAME: MemoryTracker::recordEvent
// Function address: 0x0060e610
// Purpose: Records a memory event (allocation/free) per thread, pushed onto a thread-specific stack.
// The function uses TLS to determine which stack to use and stores the event value in a global slot.

#include <cstdint>

// Global structures (defined elsewhere)
extern int gStackBase1;          // DAT_01206880
extern int gStackBase2;          // DAT_012068e8
extern int gEventStore[2];       // DAT_00f15a4c (two slots indexed by thread flag)
extern const void* gEventMarker; // PTR_LAB_01127524 (identifies event type)

// TLS offset constants (Windows TIB)
#define TLS_PTR_OFFSET 0x2c     // FS:[0x2c] -> pointer to thread-local storage
#define TLS_ENTRY_OFFSET 0x34   // Offset within TLS block to get per-thread flag (iVar1)

void __thiscall MemoryTracker::recordEvent(int eventValue)
{
    // Get per-thread flag: if zero, use stack base 1; else stack base 2.
    int threadFlag = *(int*)(**(int**)(__readfsdword(TLS_PTR_OFFSET) + TLS_ENTRY_OFFSET));
    
    // Store eventValue in a global index based on threadFlag
    // If threadFlag == 0 --> store at gEventStore[0]; else at gEventStore[1]
    (&gEventStore)[threadFlag == 0] = eventValue;
    
    // Select stack base based on thread flag
    int stackPtr;
    if (threadFlag != 0)
        stackPtr = gStackBase2;
    else
        stackPtr = gStackBase1;
    
    // Push two items onto the stack (growing by 4 bytes each)
    // stackPtr + 0x14 holds a stack pointer (current top)
    *(const void**)(stackPtr + 0x14) = gEventMarker; // Push marker address
    *(int*)(stackPtr + 0x14) += 4;
    *(const void**)(stackPtr + 0x14) = reinterpret_cast<const void*>(eventValue); // Push event value
    *(int*)(stackPtr + 0x14) += 4;
}