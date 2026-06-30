// FUNC_NAME: EAObject::~EAObject

void __fastcall EAObject::~EAObject(EAObject* this)
{
    void* ptr = this->field_0x40; // +0x40: pointer to allocated memory
    // Set vtable to the derived class vtable (likely the destructor phase)
    this->vftable = &EAObject_vtable_00e35888;
    this->field_4 = &EAObject_vtable_00e358a4;
    if (ptr != 0) {
        // Release or free related resources
        FUN_00644300();
        FUN_009c8eb0(ptr);
    }
    // Check flag at offset 0x18 (byte)
    if ((this->flags & 1) != 0) {
        int* pSomeObj = (int*)FUN_009c8f80();
        // Call virtual function at index 1 (offset 4 in vtable) with argument 0
        (*(void (__thiscall**)(int, int))(*pSomeObj + 4))(this->field_0x0c, 0);
    }
    // Destroy the critical section at offset 0x20
    DeleteCriticalSection(&this->criticalSection);
    // Finalize destruction by setting vtable to purecall
    this->field_4 = &EAObject_vtable_00e362e4;
    this->field_4 = &EAObject_vtable_00e362b8;
    this->vftable = &purecall_vtable_00e30fac;
}