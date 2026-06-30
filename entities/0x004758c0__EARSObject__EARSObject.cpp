// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this)
{
    void **ppObjectManager; // pointer to global object manager table
    int iSlotIndex; // index into the object manager pool
    void **ppSlotEntry; // pointer to a slot in the pool

    // Set vtable pointers (multiple inheritance or custom vtable layout)
    this->vtable0 = &PTR_FUN_00e32e14;      // +0x00: primary vtable
    this->vtable3C = &PTR_LAB_00e32e30;     // +0x3C: secondary vtable
    this->vtable48 = &PTR_LAB_00e32e40;     // +0x48: tertiary vtable

    // Allocate a slot from the global object manager
    // The sub-object at offset 0x18 is likely a key or list node
    iSlotIndex = FUN_004e1900(this + 0x18); // returns -1 on failure

    // Retrieve the corresponding slot entry from the manager
    ppObjectManager = (void**)DAT_012054c0; // global manager pointer
    if (iSlotIndex < 0)
    {
        ppSlotEntry = NULL;
    }
    else
    {
        ppSlotEntry = (void**)(*(int*)((char*)ppObjectManager + 0x10) + iSlotIndex * 0x18);
        if (ppSlotEntry == NULL)
        {
            ppSlotEntry = NULL;
        }
        else
        {
            ppSlotEntry = (void**)*ppSlotEntry; // dereference to get the first pointer in the slot
        }
    }

    // If the slot points back to this object, perform registration
    if (ppSlotEntry == this)
    {
        FUN_004df930(); // register or finalize initialization
    }

    // Increment reference count or attach to a list
    FUN_0046c640();
}