// FUNC_NAME: initGlobalVtablePointer
// Function at 0x00491bb0: sets up a global vtable pointer for a game subsystem.
// Calls an initialization routine (0x00492030) then stores a vtable address
// and returns a pointer to the global vtable pointer (used for singleton access).

// Global pointer to vtable (likely for a singleton or class factory)
static void** gVtablePointer = nullptr;

// External vtable defined elsewhere (data section 0x00e34550)
extern void* PTR_LAB_00e34550[];

// Forward declaration of the initialization function
void initSubsystem();  // 0x00492030

void** initGlobalVtablePointer() {
    // Call subsystem initialization (e.g., memory pools, object caches)
    initSubsystem();

    // Assign the global vtable pointer to point to the class vtable
    gVtablePointer = &PTR_LAB_00e34550[0];

    // Return address of the global pointer for external use
    return &gVtablePointer;
}