// FUNC_NAME: Destructible::release
// Function at 0x005a85e0: Custom deallocation for a base object.
// Checks a reference count flag at offset +2; if zero, calls a global deallocator.
// The class likely derives from Destructible (EA EARS engine).
void Destructible::release() {
    // Call internal destructor/release logic
    Destructible::destruct(); // FUN_005a72f0 (likely a virtual destructor or cleanup)
    
    // Check if the reference count (or allocation flag) at +2 is zero.
    // If true, the object is ready to be deallocated.
    if (*(short*)(this + 2) == 0) {
        // Obtain the allocator handle or memory pool ID
        uintptr_t allocHandle = Destructible::getAllocHandle(); // FUN_005a7440
        
        // Call the global deallocation function pointer (e.g., pool free) with size 8
        // DAT_0119caf8 is a global function pointer, possibly g_freeFunc or g_deallocFunc
        (*g_deallocFunc)(allocHandle, 8);
    }
}