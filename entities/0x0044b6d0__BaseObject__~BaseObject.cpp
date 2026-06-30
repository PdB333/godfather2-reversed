// FUNC_NAME: BaseObject::~BaseObject
/* Address: 0x0044b6d0 - Destructor, size 0xA0 */
undefined4 * __thiscall BaseObject::~BaseObject(BaseObject *this, byte flags)
{
    // Set vtable to base class vtable
    this->vtable = (void **)&PTR_FUN_00e313c8;

    // If reference count or flag at offset 0x90 is set, clean up sub-object at offset 0x4
    if (this->fieldAt0x90 != 0) {
        // Destructor for sub-object (e.g., string, handle)
        FUN_00610100(&this->fieldAt0x4);
    }

    // Set vtable to derived class vtable (final vtable before deletion)
    this->vtable = (void **)&PTR_LAB_00e2f638;

    // If bit 0 of flags is set, deallocate this object
    if ((flags & 1) != 0) {
        int *allocatorVtable = (int *)FUN_009c8f80(); // Get memory allocator interface
        // Call allocator deallocation function with size 0xA0
        (*(void (__thiscall **)(BaseObject *, uint))(*allocatorVtable + 4))(this, 0xA0);
    }

    return this;
}