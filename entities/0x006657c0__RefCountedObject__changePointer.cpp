// FUNC_NAME: RefCountedObject::changePointer
// Address: 0x006657c0
// This function manages a pointer at offset +0x08 (likely a reference-counted handle).
// It uses ESI as 'this', EDI as a 'source' object pointer, and param_1 as a 'new' object pointer.
// The logic decides whether to retain the current pointer, copy from source, or adopt the new pointer.

void RefCountedObject::changePointer(RefCountedObject* newObj) // param_1 in decompiled code
{
    // ESI holds this, EDI holds source object (pointer from caller)
    RefCountedObject* source = /* from EDI register */;

    // Compare the handle pointers at offset +0x08
    int newHandle = *(int*)((char*)newObj + 8);
    int sourceHandle = *(int*)((char*)source + 8);

    if (newHandle == sourceHandle)
    {
        // Handles already match; set this->handle to same and release newObj
        *(int*)((char*)this + 8) = newHandle;
        RefCountedObject::releasePointer(newObj); // FUN_0066bb40
        return;
    }

    // Try to allocate a new reference slot
    int slotId = RefCountedObject::allocateSlot(); // FUN_00665c30, returns -1 on failure
    if (slotId == -1)
    {
        // Failed; fall back to using source's handle
        *(int*)((char*)this + 8) = sourceHandle;
        RefCountedObject::retainPointer(); // FUN_0066c8d0 (no argument)
        return;
    }

    // Slot allocated; adopt the new handle and retain it
    *(int*)((char*)this + 8) = newHandle;
    RefCountedObject::retainPointer(newObj); // FUN_0066c8d0 with argument
}