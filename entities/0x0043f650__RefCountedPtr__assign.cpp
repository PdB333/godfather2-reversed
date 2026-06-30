// FUNC_NAME: RefCountedPtr::assign
// Function at 0x0043f650: Assigns a target object and handle to a ref-counted pointer.
// param_1 (target): pointer to an object with virtual functions at vtable offsets 4, 8, 0xC
// param_2 (handle): integer handle; if non-zero, the target is retained and handle stored
// Uses EAX as implicit 'this' pointer with fields: +8 (m_pTarget), +0xC (m_handle)

void RefCountedPtr::assign(void* target, int handle) {
    // VTable offsets: 4 = release, 8 = retain? , 0xC = cleanup?
    void** vtable = *(void***)target;

    // Retain the target (call vtable+8 with target as argument)
    ((void(*)(void*))(vtable[2]))(target);

    int retainedHandle;
    if (handle == 0) {
        retainedHandle = 0;
    } else {
        retainedHandle = FUN_004265d0(handle, target); // Possibly retain on handle
    }

    FUN_0043f8f0(target, retainedHandle); // Possibly release old associations

    // Update this pointer's fields (EAX is the this pointer)
    this->m_pTarget = target;      // +0x8
    // Call retain again? (note: no argument after setting m_pTarget)
    ((void(*)(void))(vtable[2]))(); 

    if (handle != 0) {
        retainedHandle = FUN_004265d0(handle, this->m_pTarget);
        this->m_handle = retainedHandle; // +0xC
        // Release the old handle (vtable+4 takes (handle, 0))
        ((void(*)(int,int))(vtable[1]))(handle, 0);
        // Call cleanup (vtable+0xC)
        ((void(*)(void))(vtable[3]))();
    } else {
        this->m_handle = 0; // +0xC
        ((void(*)(void))(vtable[3]))();
    }
}