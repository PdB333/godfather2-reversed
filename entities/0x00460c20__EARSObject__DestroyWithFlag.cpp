// FUNC_NAME: EARSObject::DestroyWithFlag
void __thiscall EARSObject::DestroyWithFlag(int freeMemoryFlag) {
    // Call virtual function at vtable+0x128 (likely pre-shutdown or cleanup)
    (*(void (__thiscall **)(EARSObject*))(*(uint32_t*)this + 0x128))(this);

    // If flag is set, free the memory associated with the parameter (likely this object or an associated allocation)
    if (freeMemoryFlag != 0) {
        // FUN_004608c0 - custom deallocator (expected to free memory at the address given by the flag? or use as a boolean?)
        FUN_004608c0(freeMemoryFlag);
    }

    // Perform additional cleanup always (FUN_0046edb0 - possibly finalizer or debug tracking)
    FUN_0046edb0(freeMemoryFlag);
}