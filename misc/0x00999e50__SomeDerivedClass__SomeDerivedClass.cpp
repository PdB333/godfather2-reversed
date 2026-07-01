// FUNC_NAME: SomeDerivedClass::SomeDerivedClass
// Address: 0x00999e50
// Role: Constructor for a derived class. Sets base vtable, initializes member at offset 0xC, then sets derived vtable.
// If allocFlag & 1, calls cleanup/destructor (likely for heap-allocated objects).

undefined4* __thiscall SomeDerivedClass::SomeDerivedClass(undefined4* this, byte allocFlag)
{
    // Set base class vtable (first vtable pointer)
    *this = &PTR_FUN_00d923a8;  // Base class vtable

    // Initialize member at offset 0xC (likely a pointer to a sub-object or another class)
    // FUN_009d2e70 is probably a constructor or initializer for that member
    FUN_009d2e70(this[3]);  // this[3] is at offset 0xC

    // Set derived class vtable (override base vtable)
    *this = &PTR_LAB_00e2f638;  // Derived class vtable

    // If the object was allocated with new (allocFlag & 1), call cleanup function
    // FUN_009c8eb0 might be a destructor or release function
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}