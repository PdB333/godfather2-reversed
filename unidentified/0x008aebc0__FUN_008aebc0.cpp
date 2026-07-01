// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte allocFlag)
{
    // Call base class constructor
    BaseClass::constructor();
    
    // Set vtable pointer to this class's vtable
    *this = &PTR_LAB_00e317cc;
    
    // If the object was allocated on the heap (bit 0 set), call operator delete
    // This is a common EA pattern: the constructor calls delete if the allocation flag is set,
    // typically used for placement new or to handle failure cleanup.
    if ((allocFlag & 1) != 0) {
        operatorDelete(this);
    }
    
    return this;
}