// FUNC_NAME: DerivedClass::DerivedClass
undefined4 * __thiscall DerivedClass::DerivedClass(undefined4 *this, byte allocFlag) {
    // Set vtable to base class vtable (PTR_FUN_00e32490)
    *this = &PTR_FUN_00e32490;
    // Call base class constructor
    BaseClass::BaseClass(this);
    // Update vtable to derived class vtable (PTR_LAB_00e30ea0)
    *this = &PTR_LAB_00e30ea0;
    // If dynamically allocated (allocFlag & 1), call cleanup/deallocation routine
    if (allocFlag & 1) {
        cleanupOnHeapAllocation(this);
    }
    return this;
}