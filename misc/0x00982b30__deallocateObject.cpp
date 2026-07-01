// FUNC_NAME: deallocateObject
// Function address: 0x00982b30
// Role: Memory deallocation utility that performs global cleanup before freeing the object.
// Called from numerous destructors and cleanup routines throughout the EARS engine.

// Forward declarations for callee functions
extern void preFreeCleanup(void);          // 0x009823b0
extern void earsFree(void* ptr);           // 0x009c8eb0

void deallocateObject(int param_1, void* ptr) {
    if (ptr != nullptr) {
        // Perform global pre‑free cleanup (e.g., memory tracking, thread safety)
        preFreeCleanup();
        // Release the actual memory block
        earsFree(ptr);
    }
}