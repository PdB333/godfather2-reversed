// FUNC_NAME: EARSBase::EARSBase

EARSBase* __thiscall EARSBase::EARSBase(EARSBase* this, byte flags)
{
    // Set primary vtable (base class vtable)
    this->vtable = (void**)&PTR_FUN_00e356fc; // +0x00: base vtable pointer
    
    // Set secondary vtable pointer at offset +0x08 to a pointer to LAB_00e35708
    this->secondaryVtable = (void**)&PTR_LAB_00e35708; // +0x08: might be an interface vtable
    
    // Call a virtual function from a third vtable at offset +0x0C
    // This calls the 4th virtual function of the vtable pointed to by this[3]
    ((void (*)())(
        **(int**)(this->thirdVtable) + 0x0C  // +0x0C: third vtable pointer, call virtual #4
    ))();
    
    // Swap secondary vtable to another one (possible derived class override)
    this->secondaryVtable = (void**)&PTR_LAB_00e3570c; // +0x08: set to derived vtable
    
    // Reset a global construction flag
    g_constructionFlag = 0; // _DAT_012234b0 = 0
    
    // Call a static initialization function (e.g., register class with factory)
    initializeStaticMembers(); // FUN_0049c640
    
    // If the allocation flags indicate heap allocation, call a deallocation helper
    if ((flags & 1) != 0) {
        deallocateObject(this); // FUN_009c8eb0 – possibly free if something failed?
    }
    
    return this;
}