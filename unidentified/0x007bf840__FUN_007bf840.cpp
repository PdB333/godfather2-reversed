// FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(SomeClass* this, byte flags)
{
    // Call base class constructor
    BaseClass::BaseClass(this);
    
    // If flag bit 0 is set, perform additional initialization or cleanup
    // The function called with this and size 0xA8 (168 bytes) likely handles
    // memory management or vtable setup for heap-allocated objects.
    if ((flags & 1) != 0) {
        someFunction(this, 0xa8);
    }
    
    return this;
}