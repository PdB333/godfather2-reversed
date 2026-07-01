// FUNC_NAME: SomeClass::constructor
// Address: 0x0093f2d0
// Role: Constructor for a class of size 0x8c (140 bytes). Calls base class initializer,
// then optionally allocates internal memory if flag bit 0 is set.

// __thiscall: param_1 is the 'this' pointer, param_2 is a flag byte.
// The function returns the this pointer (standard for constructors).

// Note: The base class constructor at 0x0093f1c0 is called first.
// If param_2 & 1 is nonzero, a memory allocation/initialization function
// at 0x0043b960 is called with this and size 0x8c. This might be a placement
// new or a custom allocator for the object's internal data.

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor (or static initializer)
    BaseClass::constructor(); // FUN_0093f1c0

    // If the lowest bit of flags is set, allocate or initialize
    // internal memory of size 0x8c (140 bytes)
    if ((flags & 1) != 0) {
        // FUN_0043b960 likely performs a memory allocation or
        // placement new for the object's internal data.
        // It takes the this pointer and the size.
        allocateInternalData(this, 0x8c); // FUN_0043b960
    }

    return this;
}