// FUNC_NAME: EarsObject::destroyInternal
void __thiscall EarsObject::destroyInternal(void)
{
    // +0x00: vtable pointer
    // Switch to destruction vtable to avoid re-entry issues
    *(void**)this = (void*)&PTR_FUN_00e31e4c;

    // +0x08: internal object (has a finalize method at vtable+0x0C)
    void* internalObj = *(void**)((unsigned int)this + 0x08);
    if (internalObj != 0) {
        void** internalVtable = *(void***)internalObj;
        // Call vtable[3] (offset 0x0C) -> internalObject::finalize
        typedef void (__thiscall* FinalizeFunc)(void*);
        FinalizeFunc finalizeInternal = (FinalizeFunc)internalVtable[3];
        finalizeInternal(internalObj);
    }

    // +0x1C: container object (manages child objects)
    void* container = *(void**)((unsigned int)this + 0x1C);
    if (container != 0) {
        void** containerVtable = *(void***)container;
        // +0x0C: field used as context for release (e.g., owner pointer)
        void* context = *(void**)((unsigned int)this + 0x0C);

        // vtable[1] (offset 0x04) -> container::releaseChild(void*, int)
        typedef void (__thiscall* ReleaseFunc)(void*, void*, int);
        ReleaseFunc releaseChild = (ReleaseFunc)containerVtable[1];
        releaseChild(container, context, 0);

        // +0x18: child object to be released via container (if not null)
        void* child = *(void**)((unsigned int)this + 0x18);
        if (child != 0) {
            releaseChild(container, child, 0);
        }

        // vtable[3] (offset 0x0C) -> container::finalize()
        typedef void (__thiscall* FinalizeContainerFunc)(void*);
        FinalizeContainerFunc finalizeContainer = (FinalizeContainerFunc)containerVtable[3];
        finalizeContainer(container);
    }

    // Switch vtable to final destroy state
    *(void**)this = (void*)&PTR_LAB_00e31e50;

    // Clear global reference count / activity flag
    DAT_0122341c = 0;
}