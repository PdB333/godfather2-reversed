// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

// Constructor for the main game manager. Sets up base class vtables, initializes global state,
// and optionally frees memory if the allocation flag is set.
GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, byte isHeapAllocated)
{
    // Set primary vtable (base class) at +0x00
    *this = &GodfatherGameManager_vtable;

    // Set secondary vtable pointer at +0x10 (likely for another base interface)
    this->baseVtable2 = &SomeBaseClass_vtable; // +0x10

    // Set two consecutive vtable pointers at +0x4C (offset 0x13 * 4 = 76)
    // Note: The decompiler shows two assignments to the same index – likely a bug or
    // actually two different members (e.g., at +0x4C and +0x50). We follow the output.
    this->vtableOffset76 = &AnotherVtable1;   // +0x4C
    this->vtableOffset76 = &AnotherVtable2;   // +0x4C (overwrites, may be intentional)

    // Clear the global initialization flag (0 = not yet fully initialized)
    g_gameManagerInitialized = 0; // _DAT_01130898

    // Call engine-level initialization (likely sets up subsystems or singletons)
    GodfatherGameManager::engineInit(); // FUN_005c16e0

    // If the object was heap-allocated (flag bit 0 set), deallocate its memory
    // after construction. This pattern is used in some EARS classes to allow
    // immediate disposal of temporary objects or to support custom allocators.
    if ((isHeapAllocated & 1) != 0) {
        GodfatherGameManager::deallocateMemory(this); // FUN_005c4480
    }

    return this;
}