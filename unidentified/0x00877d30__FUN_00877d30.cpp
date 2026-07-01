// FUNC_NAME: BaseClass::~BaseClass

unsigned int* __thiscall BaseClass::~BaseClass(unsigned int* this, byte flags) {
    // Destroy sub-object at offset +0x0C (this[3])
    if (this[3] != 0) {
        FUN_004daf90(this + 3);  // Sub-object destructor
    }
    // Destroy sub-object at offset +0x04 (this[1])
    if (this[1] != 0) {
        FUN_004daf90(this + 1);  // Sub-object destructor
    }
    // Set vtable to base class vtable (PTR_LAB_00e2f0c0)
    *this = (unsigned int*)&PTR_LAB_00e2f0c0;
    // If flags bit 0 is set, deallocate this object
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);  // Operator delete / deallocator
    }
    return this;
}