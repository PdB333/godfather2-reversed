// FUNC_NAME: EARSObject::destroy
void __thiscall EARSObject::destroy(void* this) {
    // Switch vtable to the "destructing" vtable (child release stage)
    *(void**)this = (void*)&PTR_FUN_00e36cb8; // +0x00 vtable pointer

    // Two child objects stored at offset +0x04 and +0x08
    void** childPtrs = (void**)((char*)this + 4);
    for (int i = 0; i < 2; i++) {
        void* child = childPtrs[i];
        if (child != NULL) {
            // Call the first virtual method (typically release/destroy) with argument 1
            void (__thiscall* releaseFunc)(void*, int) = *(void (__thiscall**)(void*, int))child;
            releaseFunc(child, 1);
        }
    }

    // Switch to the "destroyed" vtable (final state after children released)
    *(void**)this = (void*)&PTR_LAB_00e36cbc; // +0x00 vtable pointer

    // Mark global destruction complete flag
    g_bObjectDestroyed = 0; // DAT_01223398
}