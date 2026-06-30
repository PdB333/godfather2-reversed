// FUNC_NAME: HandleManager::createHandle
// Function at 0x004f7050: Creates a new object handle from a global allocator, returns handle index and success flag (always 1)
// The function enters a critical section, allocates 0x18 bytes, initializes the object, computes a handle relative to DAT_01205410,
// stores the handle in a per-thread table, and outputs the handle and flag 1 to outParams.

#include <windows.h>

// Global allocator base at DAT_0120541c (structure with critical section at +0x1b8 and fallback pointer at +0x17c)
// Global base address for handle offset calculation at DAT_01205410
extern int DAT_0120541c;   // Allocator instance
extern int DAT_01205410;   // Handle base

// Custom allocation function (size 0x18) - returns pointer to allocated block or 0
extern int* allocateMemory(int allocatorBase, int size);

// Object initializer (sets up the allocated block)
extern void initializeObject();

// Thread-local storage slot used for handle table
#define TLS_SLOT_INDEX 0x2c

void HandleManager::createHandle(int* outParams) {
    LPCRITICAL_SECTION cs;
    int* allocatedBlock;
    int handleOffset;
    int tlsValue;   // Pointer from TLS
    int tempPtr;
    int fallback;   // Used on allocation failure

    // Get the global allocator
    int allocatorBase = DAT_0120541c;

    // Critical section from allocator at offset 0x1b8
    cs = *(LPCRITICAL_SECTION*)(allocatorBase + 0x1b8);
    handleOffset = 0;   // Initialize to 0

    if (cs) {
        EnterCriticalSection(cs);
    }

    // Attempt to allocate 0x18 bytes from the allocator
    allocatedBlock = (int*)allocateMemory(allocatorBase, 0x18);

    if (allocatedBlock == 0) {
        // Allocation failed, use fallback pointer
        if (cs) {
            LeaveCriticalSection(cs);
        }
        fallback = *(int*)(allocatorBase + 0x17c);  // +0x17c: fallback pointer
    } else {
        // Success: call constructor/initializer on allocated block
        initializeObject();
        // Read value from offset 0x8 of the allocated block (e.g., an object ID or index)
        fallback = allocatedBlock[2];   // *(int*)(allocatedBlock + 8)

        if (cs) {
            LeaveCriticalSection(cs);
        }
    }

    // Compute handle as difference from base
    if (fallback != 0) {
        handleOffset = fallback - DAT_01205410;

        // Access per-thread data: get TLS pointer at FS:[0x2c]
        // The first dereference gives a thread-local block, second dereference +8 gives a table pointer
        tempPtr = *(*((int**)(((char*)__readfsdword(TLS_SLOT_INDEX)) + 0x2c)) + 8) + handleOffset;
        if (tempPtr != 0) {
            // Zero out two fields at offset 0x10 and 0x14
            *(undefined4*)(tempPtr + 0x10) = 0;
            *(undefined4*)(tempPtr + 0x14) = 0;
        }
    }

    // Output results
    outParams[0] = handleOffset;   // Handle index
    outParams[1] = 1;             // Success flag
}