// FUNC_NAME: SomeClass::SomeClass
// Address: 0x00567f50
// Role: Constructor for a class that takes a byte flag (param_2) to conditionally call an initialization or cleanup function.
// The base class constructor at 0x00568000 is called first.
// If param_2 & 1 is set, FUN_009c8eb0 is called on this object (likely a destructor or deallocation, but used in constructor? Possibly a placement new flag).

undefined4 __thiscall SomeClass::SomeClass(undefined4 this, byte param_2)
{
    // Call base class constructor (likely at offset 0x00568000)
    FUN_00568000();

    // If the low bit of param_2 is set, call a secondary function on this object
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}