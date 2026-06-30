// FUNC_NAME: EARSObject::release
// Function at 0x005d04a0: Likely a destructor or release method for a reference-counted or pointer-based object in EA EARS engine.
// Uses ESI as implicit 'this' pointer (custom calling convention or optimization).
// Pattern: release contained pointer, zero it out, then deallocate self if needed.

void EARSObject::release() {
    char cVar1;
    
    // If internal pointer (at offset 0x00 of this) is non-null, call its virtual method at vtable+4 (likely a destructor or release)
    if (this->m_pInternal != nullptr) {
        (this->m_pInternal->vtable->releaseFunc)();  // vtable+4
    }
    
    // Null out internal pointer
    this->m_pInternal = nullptr;
    
    // Attempt to deallocate self (custom deallocation function)
    cVar1 = deallocateObject(this);  // FUN_005c43d0
    if (cVar1 == '\0') {
        // If deallocation failed (e.g., object not owned by this allocator), notify a global manager
        // DAT_012234ec+4 points to some global singleton (likely a memory manager or object factory)
        // Call its virtual method at vtable+4 (could be a "unregister" or "cleanup" function)
        GLOBAL_MANAGER->vtable->onDeletionFailed();  // vtable+4
    }
}