// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x005005e0
// Role: Constructor for an object that may call a clean-up routine based on a flag.
// Calls base class constructor at 0x005001a0. If param_2's bit 0 is set, calls FUN_009c8eb0
// (likely a destructor or memory manager cleanup) on the object.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Call base class constructor (likely at offset 0 of this object)
    BaseClass::BaseClass(this);
    
    // If the flag's lowest bit is set, invoke a clean-up/destructor function.
    // This may be used for control flow (e.g., conditional destruction after construction)
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);  // potentially `this->~SomeClass()` or a custom cleanup
    }
    
    return this;
}