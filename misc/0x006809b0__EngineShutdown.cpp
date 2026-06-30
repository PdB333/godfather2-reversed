// FUNC_NAME: EngineShutdown
// Function address: 0x006809b0
// This function performs a global engine shutdown sequence: cleans up resources,
// calls destructors on global objects, and resets internal allocation tables.
// It is invoked multiple times during shutdown (via different callers).

#include <cstdint>

// External global data references (to be resolved with actual symbols)
extern void* DAT_01129924;          // Pointer to a vtable or object instance
extern uint8_t* DAT_01206880;       // Base address of some allocation/metadata region
extern void* DAT_01129904;          // Pointer to a destructible global object (or nullptr)
extern void* DAT_01129884;          // Pointer to another global object
extern void* DAT_01223418;          // Pointer to a third global object
extern void* PTR_LAB_00e5011c;      // Static pointer table used for resetting allocation

// Forward declarations of internal helper functions
void FUN_006938a0(void);            // Core cleanup step 1
void FUN_009202e0(int32_t arg);     // Set cleanup flag (arg = 1)
void FUN_0068bcd0(int32_t arg);     // Cleanup step A (arg = 0)
void FUN_0068baf0(int32_t arg);     // Cleanup step B (arg = 0)
void FUN_0043bee0(void);            // Resource flush
void FUN_00439f30(void);            // Additional cleanup routine
void FUN_00426000(void);            // Additional cleanup routine
void FUN_00424950(void);            // Additional cleanup routine
void FUN_004403f0(void);            // Final cleanup part 1
void FUN_0043c050(void);            // Final cleanup part 2

// Type for function pointer calls (used with global destructors)
typedef void (*DestructorFunc)(int32_t arg);

void EngineShutdown(void)
{
    // Step 1: Core shutdown helper
    FUN_006938a0();

    // Step 2: Set cleanup flag (argument 1)
    FUN_009202e0(1);

    // Step 3: Call a virtual function on a main engine object
    // *DAT_01129924 is likely a vtable pointer; function at offset +4 is called.
    (**(void (**)(void))(*static_cast<int32_t*>(DAT_01129924) + 4))();

    // Step 4: Adjust allocation table pointer
    // DAT_01206880 + 0x14 holds a pointer to a memory allocation table.
    // Reset it to a static default table, then advance current entry by 4 bytes.
    int32_t* pAllocPtr = reinterpret_cast<int32_t*>(DAT_01206880 + 0x14);
    *reinterpret_cast<int32_t**>(DAT_01206880 + 0x14) = &PTR_LAB_00e5011c; // reset to default
    *pAllocPtr = *pAllocPtr + 4; // advance the allocation offset

    // Step 5: Repeated cleanup (loop 4 times)
    int32_t loopCount = 4;
    do {
        FUN_0068bcd0(0);
        FUN_0068baf0(0);
        --loopCount;
    } while (loopCount != 0);

    // Step 6: Flush resources
    FUN_0043bee0();

    // Step 7: Call optional destructors on global objects if they exist
    if (DAT_01129904 != nullptr) {
        reinterpret_cast<DestructorFunc>(*static_cast<int32_t*>(DAT_01129904))(1);
    }
    if (DAT_01129884 != nullptr) {
        reinterpret_cast<DestructorFunc>(*static_cast<int32_t*>(DAT_01129884))(1);
    }
    if (DAT_01223418 != nullptr) {
        reinterpret_cast<DestructorFunc>(*static_cast<int32_t*>(DAT_01223418))(1);
    }

    // Step 8: Additional fixed cleanup functions
    FUN_00439f30();
    FUN_00426000();
    FUN_00424950();

    // Step 9: Repeat the two-step cleanup pattern once more
    FUN_0068bcd0(0);
    FUN_0068baf0(0);

    // Step 10: Final cleanup pair
    FUN_004403f0();
    FUN_0043c050();
}